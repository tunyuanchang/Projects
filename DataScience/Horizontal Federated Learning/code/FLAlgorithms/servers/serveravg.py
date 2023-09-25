from FLAlgorithms.users.useravg import UserAVG
from FLAlgorithms.servers.serverbase import Server
from utils.model_utils import read_data, read_user_data

class FedAvg(Server):
    def __init__(self, args, model, seed, logging):
        super().__init__(args, model, seed, logging)

        # Initialize data for all  users
        data = read_data(args.dataset)
        total_users = len(data[0])
        self.use_adam = 'adam' in self.algorithm.lower()
        # print("Users in total: {}".format(total_users))
        logging.info("Users in total: {}".format(total_users))

        for i in range(total_users):
            id, train_data , test_data = read_user_data(i, data, device=self.device, dataset=args.dataset)
            user = UserAVG(args, id, model, train_data, test_data, use_adam=False)
            self.users.append(user)
            self.total_train_samples += user.train_samples
            
        self.logging.info(f"Number of users per round / total users: {args.num_users} / {total_users}")
        self.logging.info("Finished creating FedAvg server.")

    def train(self, args):
        for glob_iter in range(self.num_glob_iters):
            self.logging.info(f"\n\n-------------Round number: {glob_iter} -------------\n\n")
            self.selected_users = self.select_users(glob_iter,self.num_users)
            self.send_parameters(mode=self.mode)
            self.evaluate(glob_iter)
            
            for user in self.selected_users: # allow selected users to train
                    user.train(glob_iter, personalized=self.personalized, count_labels=False)
        
            self.aggregate_parameters()
