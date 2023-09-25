import pickle
from pathlib import Path
from typing import Union

import torch
from scipy import sparse as sp

from .gcn import GCN
from .utils import check_adj, set_seed

set_seed(0)


class Judge():
    def __init__(self, data_path, model_path, input_file, device='cpu', **kwargs):
        self.model_path = model_path
        self.input_file = input_file
        self.device = device

        self.data = pickle.load(Path(data_path).open('rb'))
        self.adj, self.features, self.labels, self.idx_train, self.idx_val, self.idx_test = self.data
        self.model = self._load_model()

    def _load_model(self):
        model = GCN(nfeat=self.features.shape[1], nhid=16,
                    nclass=self.labels.max().item()+1, dropout=0.5, device=self.device)
        gcn_path = Path(self.model_path)
        if gcn_path.is_file() and isinstance(model, GCN):
            model.load_state_dict(torch.load(gcn_path, map_location=self.device))
            model = model.to(self.device)
        else:
            model = model.to(self.device)
            model.fit(self.features, self.adj, self.labels, self.idx_train, self.idx_val, patience=30, verbose=True)
            print(model.test(self.idx_test))
            torch.save(model.state_dict(), gcn_path)
        model.eval()
        return model

    def multi_test(self, func, **kwargs):
        target_nodes = []
        with Path(self.input_file).open('r') as f:
            target_nodes = [int(n) for n in f.read().split('\n')]

        cnt = 0
        misclassification_nodes = []
        degrees = self.adj.sum(0).A1
        num = len(target_nodes)
        for target_node in target_nodes:
            n_perturbations = int(degrees[target_node]) + 2
            print(f'target node={target_node}, n_perturbations={n_perturbations}')

            modified_adj = func(*self.data, target_node, n_perturbations, **kwargs)

            actural_perturbations = ((self.adj.toarray() - modified_adj.toarray()) ** 2).sum() / 2  # symmetric
            if actural_perturbations > n_perturbations:
                raise Exception(
                    f'Expect number of perturbations <= {n_perturbations}, but got {actural_perturbations}.')

            acc = self.single_test(modified_adj, target_node)
            if acc == 0:
                cnt += 1
                print('attack success')
            else:
                misclassification_nodes.append(target_node)
                print('attack failed')
            print('-'*50)
        print(f'misclassification rate : {cnt/num}')
        print(misclassification_nodes)

    def single_test(self, adj: Union[sp.spmatrix, torch.Tensor], target_node: int) -> float:
        check_adj(adj)

        output = self.model.predict(self.features, adj)
        acc_test = (output.argmax(1)[target_node] == self.labels[target_node])
        return acc_test.item()
