# train a baseline model from scratch
import argparse
from FLAlgorithms.servers.serveravg import FedAvg
import torch
from utils.log_utils import set_logger
from utils.model_utils import create_model
import os
import logging

def create_server_n_user(args, i, logging):
    model = create_model(args.model, args.dataset, args.device)
    
    if ('FedAvg' in args.algorithm):
        server = FedAvg(args, model, i, logging)
    else:
        print("Algorithm {} has not been implemented.".format(args.algorithm))
        exit()

    return server

def run_job(args, i, logging):
    torch.manual_seed(i)
    print("\n\n         [ Start training iteration {} ]           \n\n".format(i))
    # Generate model
    server = create_server_n_user(args, i, logging)
    if args.train:
        server.train(args)
        server.test()

def main(args, logging):
    for i in range(args.times):
        run_job(args, i, logging)
    print("Finished training.")

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("--dataset", type=str, default="CIFAR10")
    parser.add_argument("--model", type=str, default="resnet18")
    parser.add_argument("--train", type=int, default=1, choices=[0,1])
    # parser.add_argument("--watermark_mode", type=str, default="normal")
    # parser.add_argument("--adv_targetAcc", type=float, default=0.6, help="adversarial model accuracy")
    # parser.add_argument("--finetune_detector", type=int, default=0, choices=[0,1])

    parser.add_argument("--algorithm", type=str, default="pFedMe")
    parser.add_argument("--batch_size", type=int, default=32)
    parser.add_argument("--gen_batch_size", type=int, default=32, help='number of samples from generator')
    parser.add_argument("--learning_rate", type=float, default=0.01, help="Local learning rate")
    parser.add_argument("--personal_learning_rate", type=float, default=0.01, help="Personalized learning rate to caculate theta aproximately using K steps")
    parser.add_argument("--ensemble_lr", type=float, default=1e-4, help="Ensemble learning rate.")
    parser.add_argument("--beta", type=float, default=1.0, help="Average moving parameter for pFedMe, or Second learning rate of Per-FedAvg")
    parser.add_argument("--lamda", type=int, default=1, help="Regularization term")
    parser.add_argument("--mix_lambda", type=float, default=0.1, help="Mix lambda for FedMXI baseline")
    parser.add_argument("--embedding", type=int, default=0, help="Use embedding layer in generator network")
    parser.add_argument("--num_glob_iters", type=int, default=200)
    parser.add_argument("--local_epochs", type=int, default=20)
    parser.add_argument("--num_users", type=int, default=10, help="Number of Users per round")
    parser.add_argument("--K", type=int, default=1, help="Computation steps")
    parser.add_argument("--times", type=int, default=1, help="running time")
    parser.add_argument("--device", type=str, default="cpu", choices=["cpu","cuda"], help="run device (cpu | cuda)")
    parser.add_argument("--result_path", type=str, default="results", help="directory path to save results")

    # parser.add_argument('--save_path', default='experiments/CIFAR10/baseline/resnet18', type=str)

    args = parser.parse_args()

    if not os.path.exists(os.path.join(args.result_path, args.algorithm, "models", args.dataset)):
        os.makedirs(os.path.join(args.result_path, args.algorithm, "models", args.dataset))

    set_logger(os.path.join(args.result_path, args.algorithm, "models", args.dataset, "training.log")) #set_logger(os.path.join(args.result_path, "training.log"))
    logging.info("=" * 80)
    logging.info("Summary of normal model training process:")
    logging.info(f"Dataset: {args.dataset}")
    logging.info(f"model: {args.model}")
    logging.info(f"Device: {args.device}")
    logging.info(f"Number of global rounds: {args.num_glob_iters}")
    logging.info(f"Number of local rounds: {args.local_epochs}")
    logging.info(f"Clents' learning rate: {args.learning_rate}")
    logging.info("=" * 80)

    main(args, logging)
