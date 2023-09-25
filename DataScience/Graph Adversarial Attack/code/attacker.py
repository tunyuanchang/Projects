import numpy as np
import scipy.sparse as sp
from torch import _scaled_dot_product_efficient_attention
from torch.nn.modules.module import Module

class BaseAttack(Module):
    """Abstract base class for target attack classes.
    Parameters
    ----------
    model :
        model to attack
    nnodes : int
        number of nodes in the input graph
    device: str
        'cpu' or 'cuda'
    """

    def __init__(self, model, nnodes, device='cpu'):
        super(BaseAttack, self).__init__()
        self.surrogate = model
        self.nnodes = nnodes
        self.device = device

        self.modified_adj = None

    def attack(self, ori_adj, n_perturbations, **kwargs):
        """Generate perturbations on the input graph.
        Parameters
        ----------
        ori_adj : scipy.sparse.csr_matrix
            Original (unperturbed) adjacency matrix.
        n_perturbations : int
            Number of perturbations on the input graph. Perturbations could
            be edge removals/additions or feature removals/additions.
        Returns
        -------
        None.
        """
        raise NotImplementedError()


class RND(BaseAttack):
    def __init__(self, model=None, nnodes=None, device='cpu'):
        super(RND, self).__init__(model, nnodes, device=device)

    def attack(self, ori_features: sp.csr_matrix, ori_adj: sp.csr_matrix, labels: np.ndarray,
               idx_train: np.ndarray, target_node: int, n_perturbations: int, **kwargs):
        """
        Randomly sample nodes u whose label is different from v and
        add the edge u,v to the graph structure. This baseline only
        has access to true class labels in training set
        Parameters
        ----------
        ori_features : scipy.sparse.csr_matrix
            Original (unperturbed) node feature matrix
        ori_adj : scipy.sparse.csr_matrix
            Original (unperturbed) adjacency matrix
        labels :
            node labels
        idx_train :
            node training indices
        target_node : int
            target node index to be attacked
        n_perturbations : int
            Number of perturbations on the input graph. Perturbations could be edge removals/additions.
        """

        print(f'number of pertubations: {n_perturbations}')
        modified_adj = ori_adj.tolil()

        row = ori_adj[target_node].todense().A1
        diff_label_nodes = [x for x in idx_train if labels[x] != labels[target_node] and row[x] == 0]
        diff_label_nodes = np.random.permutation(diff_label_nodes)

        if len(diff_label_nodes) >= n_perturbations:
            changed_nodes = diff_label_nodes[: n_perturbations]
            modified_adj[target_node, changed_nodes] = 1
            modified_adj[changed_nodes, target_node] = 1
        else:
            changed_nodes = diff_label_nodes
            unlabeled_nodes = [x for x in range(ori_adj.shape[0]) if x not in idx_train and row[x] == 0]
            unlabeled_nodes = np.random.permutation(unlabeled_nodes)
            changed_nodes = np.concatenate([changed_nodes, unlabeled_nodes[: n_perturbations-len(diff_label_nodes)]])
            modified_adj[target_node, changed_nodes] = 1
            modified_adj[changed_nodes, target_node] = 1
            pass

        self.modified_adj = modified_adj


# TODO: Implemnet your own attacker here

class MyAttacker(BaseAttack):
    def __init__(self, model=None, nnodes=None, device='cpu'):
        super(MyAttacker, self).__init__(model, nnodes, device=device)
        self.W1, self.W2 = self.surrogate.state_dict().values()
        self.w = self.W1.matmul(self.W2)
        self.logit = None

    def compute_score(self, label0, label1, ori, mod):
      diff = mod - ori
      return diff[label1] - 2 * diff[label0]

    def attack(self, ori_features: sp.csr_matrix, ori_adj: sp.csr_matrix, labels: np.ndarray,
               idx_train: np.ndarray, target_node: int, n_perturbations: int, **kwargs):
        
        print(f'number of pertubations: {n_perturbations}')

        modified_adj = ori_adj.tolil()
        row = ori_adj[target_node].todense().A1
        XW = ori_features*self.w

        #find strongest wrong class
        try:
          logit = self.logit[target_node].argsort()[::-1]
        except:
          self.logit = ori_adj*ori_adj*XW
          logit = self.logit[target_node].argsort()[::-1]
        
        for i in logit:
          if i != labels[target_node]:
            wrong_class = i
            break
        correct_class = labels[target_node]

        diff_label_nodes = [x for x in idx_train if labels[x] == wrong_class and row[x] == 0]
        connected_nodes = [x for x in row.nonzero()[0]]# if labels[x] == correct_class]
        potential_nodes = diff_label_nodes + connected_nodes
        #print(len(diff_label_nodes), len(connected_nodes), len(potential_nodes))

        n_perturbations = min(n_perturbations, len(potential_nodes))

        for n in range(n_perturbations):
          max_score = -1e10
          ori_logit = (modified_adj*modified_adj*XW)[target_node]

          for i in potential_nodes:
            modified_adj[target_node, i] = 1 - row[i]
            modified_adj[i, target_node] = 1 - row[i]

            test_logit = (modified_adj*modified_adj*XW)[target_node]
            score = self.compute_score(correct_class, wrong_class, ori_logit, test_logit)

            if score >= max_score:
              max_score = score
              perturbation_node = i
            
            modified_adj[target_node, i] = row[i]
            modified_adj[i, target_node] = row[i]

          if perturbation_node not in connected_nodes:
            modified_adj[target_node, perturbation_node] = 1
            modified_adj[perturbation_node, target_node] = 1
          else:
            modified_adj[target_node, perturbation_node] = 0
            modified_adj[perturbation_node, target_node] = 0

          potential_nodes.remove(perturbation_node)

        self.modified_adj = modified_adj