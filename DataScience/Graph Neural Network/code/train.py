from argparse import ArgumentParser

from data_loader import load_data

import torch
import torch.nn as nn
from dgl.sampling import node2vec_random_walk

from model import GCN, GNNModel
# from model import YourGNNModel # Build your model in model.py
    
import os
import warnings
warnings.filterwarnings("ignore")

def evaluate(g, features, labels, mask, model):
    """Evaluate model accuracy"""
    model.eval()
    with torch.no_grad():
        logits = model(g, features)
        logits = logits[mask]
        _, indices = torch.max(logits, dim=1)
        correct = torch.sum(indices == labels)
        return correct.item() * 1.0 / len(labels)

def train(g, features, train_labels, val_labels, train_mask, val_mask, model, epochs, es_iters=None):
    
    # define train/val samples, loss function and optimizer
    loss_fcn = nn.CrossEntropyLoss()
    optimizer = torch.optim.Adam(model.parameters(), lr=3e-2, weight_decay=5e-4)

    # If early stopping criteria, initialize relevant parameters
    if es_iters:
        print("Early stopping monitoring on")
        loss_min = 1e8
        es_i = 0

    # training loop
    for epoch in range(epochs):
        model.train()
        logits = model(g, features)
        loss = loss_fcn(logits[train_mask], train_labels)
        optimizer.zero_grad()
        loss.backward(retain_graph=True)
        optimizer.step()

        acc0 = evaluate(g, features, train_labels, train_mask, model)
        acc1 = evaluate(g, features, val_labels, val_mask, model)
        print(
            "Epoch {:05d} | Loss {:.4f} | Accuracy {:.4f}, {:.4f}".format(
                epoch, loss.item(), acc0, acc1, 
            )
        )
        
        val_loss = loss_fcn(logits[val_mask], val_labels).item()
        if es_iters:
            if val_loss < loss_min:
                loss_min = val_loss
                es_i = 0
            else:
                es_i += 1

            if es_i >= es_iters:
                print(f"Early stopping at epoch={epoch+1}")
                break


if __name__ == '__main__':

    parser = ArgumentParser()
    # you can add your arguments if needed
    parser.add_argument('--epochs', type=int, default=300)
    parser.add_argument('--es_iters', type=int, help='num of iters to trigger early stopping')
    parser.add_argument('--use_gpu', action='store_true')
    args = parser.parse_args()

    if args.use_gpu:
        device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
    else:
        device = torch.device("cpu")

    # Load data
    features, graph, num_classes, \
    train_labels, val_labels, test_labels, \
    train_mask, val_mask, test_mask = load_data()
    
    
    print('Random Walk...')
    walk = 2
    feat = torch.zeros([features.shape[0], features.shape[1]*(walk+1)], dtype=torch.float32)
    random_walk = node2vec_random_walk(graph, graph.nodes(), 1, 0.5, walk)
    for i, v in enumerate(random_walk):
      feat[i] = torch.flatten(features[v])
    
    #feat = features
    print(feat.shape)
    # Initialize the model (Baseline Model: GCN)
    """TODO: build your own model in model.py and replace GCN() with your model"""
    in_size = feat.shape[1]
    out_size = num_classes
    model = GNNModel(in_size, 16, out_size).to(device)
    
    # model training
    print("Training...")
    train(graph, feat, train_labels, val_labels, train_mask, val_mask, model, args.epochs, args.es_iters)
    
    print("Testing...")
    model.eval()
    with torch.no_grad():
        logits = model(graph, feat)
        logits = logits[test_mask]
        _, indices = torch.max(logits, dim=1)
    
    # Export predictions as csv file
    print("Export predictions as csv file.")
    with open('output.csv', 'w') as f:
        f.write('Id,Predict\n')
        for idx, pred in enumerate(indices):
            f.write(f'{idx},{int(pred)}\n')
    # Please remember to upload your output.csv file to Kaggle for scoring
