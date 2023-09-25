# Data Science HW5

## Please install anaconda & cuda 11.3 (if you want to use gpu) first.

## Create the Environment
```
conda create --name hw5 -y
conda activate hw5
conda install pytorch==1.12.1 torchvision==0.13.1 torchaudio==0.12.1 cudatoolkit=11.3 -c pytorch
conda install scipy numpy -y
```
* without gpu support
```
conda install pytorch torchvision torchaudio cpuonly -c pytorch -y
```

## Run
```
python3 main.py 
```
* You can pass arguments like this.
```
python3 main.py --input_file target_nodes_list.txt --data_path ./data/data.pkl --model_path saved-models/gcn.pt
```

## Dataset
* Cora citation network
* Select the largest connected components of the graph and use 10%/10% nodes for training/validation.
* Stats:
  
| #nodes | #edges | #features | #classes |
|--------|--------|-----------|----------|
| 2485   | 10138  | 1433      | 7        |

## TODO
* attacker.py
  * implement your own attacker
* main.py
  * setup your attacker
