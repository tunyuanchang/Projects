import torch
import torch.nn as nn
import torch.nn.functional as F
from torch.utils.data import DataLoader
import copy
from utils.model_utils import get_dataset_name
from utils.model_config import RUNCONFIGS

class User:
    """
    Base class for users in federated learning.
    """
    def __init__(
            self, args, id, model, train_data, test_data, use_adam=False):
        self.model = copy.deepcopy(model[0])
        self.model_name = model[1]
        self.id = id  # integer
        self.train_samples = len(train_data)
        self.test_samples = len(test_data)
        self.beta = args.beta
        self.lamda = args.lamda
        self.local_epochs = args.local_epochs
        self.algorithm = args.algorithm
        self.K = args.K
        self.dataset = args.dataset
        dataset_name = get_dataset_name(self.dataset)
        self.unique_labels = RUNCONFIGS[dataset_name]["unique_labels"]

        self.batch_size = RUNCONFIGS[dataset_name]["batch_size"] 
        self.learning_rate = RUNCONFIGS[dataset_name]["learning_rate"]
        self.gamma = RUNCONFIGS[dataset_name]["gamma"] 
        self.schedule = RUNCONFIGS[dataset_name]["schedule"]

        self.trainloader = DataLoader(train_data, self.batch_size, shuffle=True, drop_last=True)
        self.testloader =  DataLoader(test_data, self.batch_size, drop_last=False)
        self.testloaderfull = DataLoader(test_data, self.test_samples)
        self.trainloaderfull = DataLoader(train_data, self.train_samples)
        self.iter_trainloader = iter(self.trainloader)
        self.iter_testloader = iter(self.testloader)

        # those parameters are for personalized federated learning.
        self.local_model = copy.deepcopy(list(self.model.parameters()))
        self.personalized_model_bar = copy.deepcopy(list(self.model.parameters()))
        self.prior_decoder = None
        self.prior_params = None

        self.init_loss_fn()
        if use_adam:
            self.optimizer=torch.optim.Adam(
                params=self.model.parameters(),
                lr=self.learning_rate, betas=(0.9, 0.999),
                eps=1e-08, weight_decay=1e-2, amsgrad=False)
        else: 
            self.optimizer = torch.optim.SGD(self.model.parameters(), lr=self.learning_rate, momentum=0.9, weight_decay=5e-4)

        self.label_counts = {}

        self.device = args.device 
        self.save_path = args.result_path 

    def init_loss_fn(self):
        self.loss= nn.CrossEntropyLoss() # nn.NLLLoss()
        self.KLD_loss = nn.KLDivLoss(reduction="batchmean")
        
        self.dist_loss = nn.MSELoss()
        self.ce_loss = nn.CrossEntropyLoss()

    def set_parameters(self, model, beta=1):
        # replace user's local model with global model
        # user's model parameters = beta*global model parameters + (1-beta)*user's model parameters
        # state_dict - get model parameters
        # load_state_dict - update model parameters
        user_model_dict = self.model.state_dict()
        for key, parameters in user_model_dict.items():
            user_model_dict[key] = beta*model.state_dict()[key] \
                                    + (1-beta)*self.model.state_dict()[key]
        self.model.load_state_dict(user_model_dict)

        ## TODO
        '''
        Replace the user's local model with the global model
        Args: 
            model: the global model parameters 
            beta: moving average model, 
                i.e., user's model parameters = beta * global model parameters + (1 - beta) * user's model parameters
        Return:
            None
        
        Hint:
            1. You can use self.model (the user's model), model (global model parameters).
        '''
        

    def set_shared_parameters(self, model, mode='decode'):
        # only copy shared parameters to local
        for old_param, new_param in zip(
                self.model.get_parameters_by_keyword(mode),
                model.get_parameters_by_keyword(mode)
        ):
            old_param.data = new_param.data.clone()

    def get_parameters(self):
        for param in self.model.parameters():
            param.detach()
        return self.model.parameters()


    def clone_model_paramenter(self, param, clone_param):
        with torch.no_grad():
            for param, clone_param in zip(param, clone_param):
                clone_param.data = param.data.clone()
        return clone_param
    
    def get_updated_parameters(self):
        return self.local_weight_updated
    
    def update_parameters(self, new_params, keyword='all'):
        for param , new_param in zip(self.model.parameters(), new_params):
            param.data = new_param.data.clone()

    def test(self):
        self.model.eval()
        test_acc = 0
        loss = 0
        for x, y in self.testloaderfull:
            x = x.to(self.device)
            y = y.to(self.device)
            output = self.model(x)['output']
            loss += self.loss(output, y)

            test_acc += (torch.sum(torch.argmax(output, dim=1) == y)).detach().item() ## 修改detach
        return test_acc, loss.detach(), y.shape[0]

    def get_next_train_batch(self, count_labels=True):
        try:
            # Samples a new batch for personalizing
            (X, y) = next(self.iter_trainloader)
        except StopIteration:
            # restart the generator if the previous generator is exhausted.
            self.iter_trainloader = iter(self.trainloader)
            (X, y) = next(self.iter_trainloader)
        result = {'X': X, 'y': y}
        if count_labels:
            unique_y, counts=torch.unique(y, return_counts=True)
            unique_y = unique_y.detach().numpy()
            counts = counts.detach().numpy()
            result['labels'] = unique_y
            result['counts'] = counts
        return result

    def get_next_test_batch(self):
        try:
            # Samples a new batch for personalizing
            (X, y) = next(self.iter_testloader)
        except StopIteration:
            # restart the generator if the previous generator is exhausted.
            self.iter_testloader = iter(self.testloader)
            (X, y) = next(self.iter_testloader)
        return (X, y)
