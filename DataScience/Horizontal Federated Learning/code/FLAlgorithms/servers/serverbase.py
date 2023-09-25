import torch
import os
import numpy as np
import h5py
from utils.model_utils import RUNCONFIGS #, get_dataset_name
import copy
import torch.nn.functional as F
import torch.nn as nn
from utils.model_utils import get_log_path, METRICS

class Server:
    def __init__(self, args, model, seed, logging):
        self.logging = logging
        # Set up the main attributes
        self.dataset = args.dataset
        self.num_glob_iters = args.num_glob_iters
        self.local_epochs = args.local_epochs
        self.batch_size = args.batch_size
        self.learning_rate = args.learning_rate
        self.total_train_samples = 0
        self.K = args.K
        self.model = copy.deepcopy(model[0])
        self.model_name = model[1]
        self.users = []
        self.selected_users = []
        self.num_users = args.num_users
        self.beta = args.beta
        self.lamda = args.lamda
        self.algorithm = args.algorithm
        self.personalized = 'pFed' in self.algorithm
        self.mode='partial' if 'partial' in self.algorithm.lower() else 'all'
        self.seed = seed
        self.deviations = {}
        self.metrics = {key:[] for key in METRICS}
        self.timestamp = None
        self.save_path = args.result_path
        os.system("mkdir -p {}".format(self.save_path))
        
        # 自己新增
        self.device = args.device
        self.best_accu = 0
        self.best_loss = 1e9
        self.best_iter = -1

    def send_parameters(self, mode='all', beta=1, selected=False):
        users = self.users
        if selected:
            assert (self.selected_users is not None and len(self.selected_users) > 0)
            users = self.selected_users
        for user in users:
            if mode == 'all': # share only subset of parameters
                user.set_parameters(self.model,beta=beta)
            else: # share all parameters
                user.set_shared_parameters(self.model,mode=mode)

    def aggregate_parameters(self):
        n_samples = []
        states = []
        # pick selected users' number of samples and model parameters
        for user in self.selected_users:
            n_samples.append(user.train_samples)
            states.append(user.model.state_dict())
        # calculate weight for each selected user
        N = sum(n_samples)
        weights = [n/N for n in n_samples]
        # weighted sum all selected users' model parameters and update global model
        global_model_dict = self.model.state_dict()
        for key, parameters in global_model_dict.items():
            for i in range(len(self.selected_users)):
                if i == 0:
                    global_model_dict[key] = weights[i] * states[i][key]
                else:
                    global_model_dict[key] += weights[i] * states[i][key]
        self.model.load_state_dict(global_model_dict)

      ## TODO
        '''
        Weighted sum all the selected users' model parameters by number of samples
        
        Args: None
        Return: None

        Hints:
            1. Use self.selected_users, user.train_samples.
            2. Replace the global model (self.model) with the aggregated model.
        '''

    def save_model(self):
        model_path = os.path.join(self.save_path, self.algorithm, "models", self.dataset)
        if not os.path.exists(model_path):
            os.makedirs(model_path)
        torch.save(self.model, os.path.join(model_path, "best_server" + ".pt"))


    def load_model(self):
        model_path = os.path.join(self.save_path, "models", self.dataset, "server" + ".pt")
        assert (os.path.exists(model_path))
        self.model = torch.load(model_path)

    def model_exists(self):
        return os.path.exists(os.path.join("models", self.dataset, "server" + ".pt"))
    
    def select_users(self, round, num_users):
        import random
        # guarantee num_users <= len(self.users)
        num_users = min(num_users, len(self.users))
        # random selection
        selected_idx = random.sample(range(len(self.users)), num_users)

        selected_objects = []
        for i in range(num_users):
            selected_objects.append(self.users[selected_idx[i]])
            
        return selected_objects

        ## TODO
        '''
        Randomly select {num_users} users from all users
        Args:
            round: current round
            num_users: number of users to select
        Return:
            List of selected clients objects

        Hints:
            1. Default 10 users to select, you can modify the args {--num_users} to change this hyper-parameter
            2. Note that {num_users} can not be larger than total users (i.e., num_users <= len(self.user))
        '''

    def init_loss_fn(self):
        self.loss= nn.CrossEntropyLoss()# nn.NLLLoss()
        self.ensemble_loss=nn.KLDivLoss(reduction="batchmean")#,log_target=True)
        self.ce_loss = nn.CrossEntropyLoss()


    def save_results(self, args):
        alg = get_log_path(args, args.algorithm, self.seed, args.gen_batch_size)
        with h5py.File("./{}/{}.h5".format(self.save_path, alg), 'w') as hf:
            for key in self.metrics:
                hf.create_dataset(key, data=self.metrics[key])
            hf.close()
        

    def test(self, selected=False):
        '''tests self.latest_model on given clients
        '''
        num_samples = []
        tot_correct = []
        losses = []
        users = self.selected_users if selected else self.users
        for c in users:
            # print(f"client id: {c.id}")
            ct, c_loss, ns = c.test()
            tot_correct.append(ct*1.0)
            num_samples.append(ns)
            losses.append(c_loss)
        ids = [c.id for c in self.users]

        return ids, num_samples, tot_correct, losses



    def test_personalized_model(self, selected=True):
        '''tests self.latest_model on given clients
        '''
        num_samples = []
        tot_correct = []
        losses = []
        users = self.selected_users if selected else self.users
        for c in users:
            ct, ns, loss = c.test_personalized_model()
            tot_correct.append(ct*1.0)
            num_samples.append(ns)
            losses.append(loss)
        ids = [c.id for c in self.users]

        return ids, num_samples, tot_correct, losses

    def evaluate_personalized_model(self, selected=True, save=True):
        stats = self.test_personalized_model(selected=selected)
        test_ids, test_num_samples, test_tot_correct, test_losses = stats[:4]
        glob_acc = np.sum(test_tot_correct)*1.0/np.sum(test_num_samples)
        test_loss = np.sum([x * y for (x, y) in zip(test_num_samples, test_losses)]).item() / np.sum(test_num_samples)
        if save:
            self.metrics['per_acc'].append(glob_acc)
            self.metrics['per_loss'].append(test_loss)
        print("Average Global Accurancy = {:.4f}, Loss = {:.2f}.".format(glob_acc, test_loss))


    def evaluate_ensemble(self, selected=True):
        self.model.eval()
        users = self.selected_users if selected else self.users
        test_acc=0
        loss=0
        for x, y in self.testloaderfull:
            target_logit_output=0
            for user in users:
                # get user logit
                user.model.eval()
                user_result=user.model(x, logit=True)
                target_logit_output+=user_result['logit']
            target_logp=F.log_softmax(target_logit_output, dim=1)
            test_acc+= torch.sum( torch.argmax(target_logp, dim=1) == y ) #(torch.sum().item()
            loss+=self.loss(target_logp, y)
        loss = loss.detach().numpy()
        test_acc = test_acc.detach().numpy() / y.shape[0]
        self.metrics['glob_acc'].append(test_acc)
        self.metrics['glob_loss'].append(loss)
        print("Average Global Accurancy = {:.4f}, Loss = {:.2f}.".format(test_acc, loss))


    def evaluate(self, iter, save=True, selected=False):
        # override evaluate function to log vae-loss.
        test_ids, test_samples, test_accs, test_losses = self.test(selected=selected)
        glob_acc = np.sum(test_accs)*1.0/np.sum(test_samples)
        test_losses = [t.detach().cpu().numpy() for t in test_losses] # Error: RuntimeError: Can't call numpy() on Tensor that requires grad. #15
        glob_loss = np.sum([x * y for (x, y) in zip(test_samples, test_losses)]).item() / np.sum(test_samples)
        if save:
            self.metrics['glob_acc'].append(glob_acc)
            self.metrics['glob_loss'].append(glob_loss)
        # print("Average Global Accurancy = {:.4f}, Loss = {:.2f}.".format(glob_acc, glob_loss))

        if glob_acc > self.best_accu:
            self.best_accu = glob_acc
            self.best_loss = glob_loss
            self.best_iter = iter
            self.save_model()


        self.logging.info("Average Global Accurancy = {:.4f}, Loss = {:.2f}.".format(glob_acc, glob_loss))
        self.logging.info("Best Global Accurancy = {:.4f}, Loss = {:.2f}, Iter = {:}.".format(self.best_accu, self.best_loss, self.best_iter))
