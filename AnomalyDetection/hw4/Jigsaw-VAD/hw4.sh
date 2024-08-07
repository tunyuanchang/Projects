#!/bin/bash

# data preparation
python gen_patches.py --dataset avenue --phase train --filter_ratio 0.9 --sample_num 5
python gen_patches.py --dataset avenue --phase test --filter_ratio 0.9 --sample_num 5

# training/testing
printf "\nproblem 1\n"
python3 main.py --dataset avenue --val_step 875 --print_interval 175 \
                --batch_size 256 --sample_num 5 --epochs 20 --static_threshold 0.2


python3 main.py --dataset avenue --sample_num 5 --checkpoint best_1.pth

printf "\nproblem 2\n"
python3 main2.py --dataset avenue --val_step 875 --print_interval 175 \
                --batch_size 256 --sample_num 5 --epochs 20 --static_threshold 0.2


python3 main2.py --dataset avenue --sample_num 5 --checkpoint best_2.pth

printf "\nproblem 3\n"
python3 main3.py --dataset avenue --val_step 875 --print_interval 175 \
                --batch_size 256 --sample_num 5 --epochs 20 --static_threshold 0.2


python3 main3.py --dataset avenue --sample_num 5 --checkpoint best_3.pth