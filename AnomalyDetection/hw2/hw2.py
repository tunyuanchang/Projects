import pandas as pd
import numpy as np

# add library
from sklearn.neighbors import NearestNeighbors
from sklearn.decomposition import PCA

from sklearn.metrics import roc_auc_score
from sklearn.metrics import pairwise_distances

import matplotlib.pyplot as plt

np.random.seed(0)

def resample(data, label, outlier_ratio=0.01, target_label=0):
    """
    Resample the data to balance classes.

    Parameters:
        data: np.array, shape=(n_samples, n_features)
            Input data.
        label: np.array, shape=(n_samples,)
            Labels corresponding to the data samples.
        outlier_ratio: float, optional (default=0.01)
            Ratio of outliers to include in the resampled data.
        target_label: int, optional (default=0)
            The label to be treated as normal.

    Returns:
        new_data: np.array
            Resampled data.
        new_label: np.array
            Resampled labels.
    """
    new_data = []
    new_label = []
    for i in [1, -1]:
        if i != target_label:
            i_data = data[label == i]
            target_size = len(data[label == target_label])
            num = target_size * outlier_ratio
            idx = np.random.choice(
                list(range(len(i_data))), int(num), replace=False
            )
            new_data.append(i_data[idx])
            new_label.append(np.ones(len(idx)) * 1)
        else:
            new_data.append(data[label == i])
            new_label.append(np.ones(len(data[label == i])) * 0)
    new_data = np.concatenate(new_data)
    new_label = np.concatenate(new_label)
    return new_data, new_label

## visualization
def random_choice(data, label, num_normal, num_anomaly, label_normal, label_anomaly):
    normal = data[label == label_normal]
    if num_normal < len(normal):
        idx = np.random.choice(len(normal), num_normal, replace=False)
        normal_data = np.array([normal[idx[i]] for i in range(num_normal)])
    else:
        normal_data = normal
    
    anomaly = data[label == label_anomaly]
    if num_anomaly < len(anomaly):
        idx = np.random.choice(len(anomaly), num_anomaly, replace=False)
        anomaly_data = np.array([anomaly[idx[i]] for i in range(num_anomaly)])
    else:
        anomaly_data = anomaly
    
    return len(normal_data), np.concatenate((normal_data, anomaly_data), axis=0)

def visualization(data, num_normal, title):
    num, feat = data.shape
    
    plt.figure(figsize=(5, 8))
    plt.suptitle(f'Dataset {title}')

    x = np.linspace(1, feat, feat)
    
    plt.subplot(211)
    for i in range(num_normal):
        plt.plot(x, data[i], color = 'b')
    plt.title('Normal Sample')
    
    plt.subplot(212)
    for i in range(num_normal, num):
        plt.plot(x, data[i], color = 'r')
    plt.title('Anomaly Sample')
    
    plt.show()
    return

## roc_auc_score
def score(label, anomaly_score):
     return roc_auc_score(label, anomaly_score)
    
## plot(x - hyperparameter; y - roc_auc_score)
def plot(scores, metric, hyperparameter, category):
    best_hyperparameter, best_score = max(scores, key=lambda x: x[1])
    print(f'{metric} anomaly detection ({category} Dataset): \n \
          {hyperparameter} = {best_hyperparameter}, score = {best_score:.4f}')
    
    plt.plot(*list(zip(*scores)), color = 'dodgerblue')
    plt.ylabel('score')
    plt.xlabel(hyperparameter)
    plt.title(f'{metric} Anomaly Detection\n({category})')
    plt.show()
    
    return best_hyperparameter, best_score

## KNN
def KNN_ad(training, testing, k=5):
    knn_model = NearestNeighbors(n_neighbors=k, metric='euclidean').fit(training)
    dist, _ = knn_model.kneighbors(testing)
    
    return np.mean(dist, axis=1)

## PCA
def PCA_reconstruction(training, testing, N):
    pca_model = PCA(n_components = N).fit(training)
    data = pca_model.inverse_transform(pca_model.transform(testing))
    errors = pairwise_distances(testing, data, metric='euclidean')
    
    return errors.diagonal()

def PCA_visualization(training, testing, label, N, category):
    pca_model = PCA(n_components = N).fit(training)
    
    num_normal, data = random_choice(testing, label, 10, 10, 0, 1)
    chosen_data = pca_model.inverse_transform(pca_model.transform(data))
    visualization(chosen_data, num_normal, category + f'\nN={N}')
    return

## DFT
def DFT_ad(training, testing, n_features, M, k=5):
    freq = np.argsort(np.abs(np.fft.fftfreq(n_features)))[:M]
    
    train_dft = np.fft.fft(training)[:, freq]
    test_dft = np.fft.fft(testing)[:, freq]
    
    train_feat = train_dft.real
    test_feat = test_dft.real
    
    return KNN_ad(train_feat, test_feat, k) # anomaly_score

def DFT_visualization(data, label, n_features, M, category):
    num_normal, chosen_data = random_choice(data, label, 10, 10, 0, 1)
    
    dft = np.fft.fft(chosen_data)
    indices = np.argsort(np.abs(np.fft.fftfreq(n_features)))[:M]
    
    dft_mask = np.zeros_like(dft, dtype=np.complex128)
    rows = np.arange(chosen_data.shape[0])[:, np.newaxis]
    dft_mask[rows, indices] = dft[rows, indices]
        
    inverse_dft = np.fft.ifft(dft_mask).real
    visualization(inverse_dft, num_normal, category + f'\nM={M}')
    return

## DWT
def padding(training, testing, n_features):
    levels = int(np.ceil(np.log2(n_features)))
    padding_shape = ((0, 0) , (0, int(2**levels) - n_features))
    train_padding = np.pad(train_data, padding_shape)
    test_padding = np.pad(test_data, padding_shape)

    return levels, train_padding, test_padding

def Discrete_Wavelet_Transform(training, testing, levels):
    n, feat = training.shape
    m, feat = testing.shape
    
    train_avg = np.zeros((levels+1, feat))
    test_avg = np.zeros((levels+1, feat))
    
    train_diff = np.zeros((levels+1, feat))
    test_diff = np.zeros((levels+1, feat))
    
    train_feat = np.zeros((n, feat))
    test_feat = np.zeros((m, feat))
    
    for i in range(n):
        train_avg[0] = training[i]
        for row in range(1, levels+1):
            for col in range(0, feat, 2):
                train_avg[row, col//2] = (train_avg[row-1, col] + train_avg[row-1, col+1])/2
                train_diff[row, col//2] = (train_avg[row-1, col+1] - train_avg[row-1, col])/2
        
        feat_vector = [train_avg[levels, 0]]
        for row in range(levels):
            feat_vector = np.append(feat_vector, train_diff[levels-row, :int(2**row)])
            
        train_feat[i] = feat_vector
    
    for i in range(m):
        test_avg[0] = testing[i]
        for row in range(1, levels+1):
            for col in range(0, feat, 2):
                test_avg[row, col//2] = (test_avg[row-1, col] + test_avg[row-1, col+1])/2
                test_diff[row, col//2] = (test_avg[row-1, col+1] - test_avg[row-1, col])/2
        
        feat_vector = [test_avg[levels, 0]]
        for row in range(levels):
            feat_vector = np.append(feat_vector, test_diff[levels-row, :int(2**row)])
            
        test_feat[i] = feat_vector
        
    return train_feat, test_feat
    
def DWT_ad(training, testing, Si, k=5):
    S = int(2**Si)
    train_feat = training[:,:S]
    test_feat = testing[:,:S]
    
    return KNN_ad(train_feat, test_feat, k) # anomaly_score

if __name__=='__main__':
    # Load the data
    # category = "ECG200" # Wafer / ECG200
    for category in ["Wafer", "ECG200"]:
        print(f"Dataset: {category}")
        train_data = pd.read_csv(f'./{category}/{category}_TRAIN.tsv', sep='\t', header=None).to_numpy()
        test_data = pd.read_csv(f'./{category}/{category}_TEST.tsv', sep='\t', header=None).to_numpy()

        train_label = train_data[:, 0].flatten()
        train_data = train_data[:, 1:]
        
        test_label = test_data[:, 0].flatten()
        test_data = test_data[:, 1:]

        ## (1) Visualization
        num_normal, data = random_choice(test_data, test_label, 10, 10, 1, -1)
        visualization(data, num_normal, category)

        train_data, train_label = resample(train_data, train_label, outlier_ratio=0.0, target_label=1)
        test_data, test_label = resample(test_data, test_label, outlier_ratio=0.1, target_label=1)

        n_samples, n_features = test_data.shape
        
        ## (2) KNN
        k = 5
        result = KNN_ad(train_data, test_data, k)
        print(f'KNN anomaly detection ({category} Dataset): K = {k}, score = {score(test_label, result):.4f}')

        ## (3) PCA
        PCA_score = []
        for n in range(1, min(n_samples, n_features)): # hyperparameter
            result = PCA_reconstruction(train_data, test_data, n)
            PCA_score.append([n, score(test_label, result)])

        best_n, _ = plot(PCA_score, 'PCA', 'N', category)
        PCA_visualization(train_data, test_data, test_label, best_n, category)

        ## (4) DFT
        DFT_score = []
        for m in range(1, n_features): # hyperparameter
            result = DFT_ad(train_data, test_data, n_features, m)
            DFT_score.append([m, score(test_label, result)])
        
        best_m, _ = plot(DFT_score, 'DFT', 'M', category)
        DFT_visualization(test_data, test_label, n_features, best_m, category)

        ## (5) DWT
        levels, train_padding, test_padding = padding(train_data, test_data, n_features)
        train_feat, test_feat = Discrete_Wavelet_Transform(train_padding, test_padding, levels)
        
        DWT_score = []
        for si in range(levels+1): # hyperparameter
            s = int(2**si)
            result = DWT_ad(train_feat, test_feat, s)
            DWT_score.append([s, score(test_label, result)])
            
        best_s, _ = plot(DWT_score, 'DWT', 'S', category)

        ## Bonus
        ### KNN for different k
        KNN_score = []
        for k in range(1, 11): ## hyperparameter
            result = KNN_ad(train_data, test_data, k)
            KNN_score.append([k, score(test_label, result)])
            
        best_k, _ = plot(KNN_score, 'KNN', 'K', category)

        ### DFT for different k
        KNN_score = []
        for k in range(1, 11): ## hyperparameter
            result = DFT_ad(train_data, test_data, n_features, best_m, k)
            KNN_score.append([k, score(test_label, result)])
            
        best_k, _ = plot(KNN_score, 'DFT', 'K', category)
        
        ### DWT for different k
        KNN_score = []
        for k in range(1, 11): ## hyperparameter
            result = DWT_ad(train_feat, test_feat, best_s, k)
            KNN_score.append([k, score(test_label, result)])
            
        best_k, _ = plot(KNN_score, 'DWT', 'K', category)