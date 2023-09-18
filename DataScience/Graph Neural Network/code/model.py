import torch
import dgl
import torch.nn as nn
import torch.nn.functional as F
from dgl.nn.pytorch import GraphConv, SAGEConv, ChebConv

class GCN(nn.Module):
    """
    Baseline Model:
    - A simple two-layer GCN model, similar to https://github.com/tkipf/pygcn
    - Implement with DGL package
    """
    def __init__(self, in_size, hid_size, out_size):
        super().__init__()
        self.layers = nn.ModuleList()
        # two-layer GCN
        self.layers.append(
            GraphConv(in_size, hid_size, activation=F.relu)
        )
        self.layers.append(GraphConv(hid_size, out_size))
        self.dropout = nn.Dropout(0.5)

    def forward(self, g, features):
        h = features
        for i, layer in enumerate(self.layers):
            if i != 0:
                h = self.dropout(h)
            h = layer(g, h)
        return h
    
class GNNModel(nn.Module):
#     """
#     TODO: Use GCN model as reference, implement your own model here to achieve higher accuracy on testing data
#     """
    def __init__(self, in_size, hid_size, out_size):
        super(GNNModel, self).__init__()
        self.layers = nn.ModuleList()

        self.layers.append(SAGEConv(in_size, 256, aggregator_type='gcn'))
        self.layers.append((ChebConv(256, 32, 3)))
        self.fc = nn.Linear(32, out_size)

        self.dropout = nn.Dropout(0.5)

    def forward(self, g, features):
        h = features 
        for i, layer in enumerate(self.layers):
          if i != 0: h = self.dropout(h)
          h = layer(g, h)
          #h = F.relu(h)
          h = F.leaky_relu(h)
        
        h = self.dropout(h)
        h = self.fc(h)
        return h
