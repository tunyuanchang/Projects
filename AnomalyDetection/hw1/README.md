# CS5658 Anomaly Detection: Homework1 – MNIST
###### Author: Tun-Yuan Chang
## Requirements
python >= 3.10
tqdm
torch
numpy
matplotlib
torchvision
scikit-learn

## Run code
python3 hw1.py

* Make sure your python version is greater than 3.10, otherwise it will fail to run.
You can use 'python --version' to check the python version.

## Result
```
======result of KNN======
K = 1: 0.9611
K = 5: 0.9663
K = 10: 0.9647
=========================

=====result of KMeans====
K = 1: 0.8954
K = 5: 0.9464
K = 10: 0.9575
=========================

========result of Distance-Based========
Cosine distance: 0.9795
Minkowski(L1 norm) distance: 0.9520
Minkowski(L2 norm) distance: 0.9558
Minkowski(L-inf norm) distance: 0.9564
Mahalanobis distance: 0.9799
========================================

========result of Density-Based========
Local Outlier Factor: 0.7930
========================================
```