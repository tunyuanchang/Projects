
########################################################
########  Do not modify the sample code segment ########
########################################################

import torchvision
import numpy as np
import torch
import tqdm
from sklearn.metrics import roc_auc_score

# Add: Library
from sklearn.metrics import pairwise_distances
from sklearn.manifold import TSNE

import matplotlib.pyplot as plt

seed = 0
np.random.seed(seed)

def resample_total(data,label,ratio=0.05):
    """
        data: np.array, shape=(n_samples, n_features)
        label: np.array, shape=(n_samples,)
        ratio: float, ratio of samples to be selected
    """
    new_data = []
    new_label = []
    for i in range(10):
        i_data = data[label==i]
        idx = np.random.choice(list(range(len(i_data))),int(len(i_data)*ratio))
        new_data.append(i_data[idx])
        new_label.append(np.ones(len(idx))*i)
    new_data = np.concatenate(new_data)
    new_label = np.concatenate(new_label)
    return new_data, new_label

def resample(data,label,outlier_ratio=0.01,target_label=0):
    """
        data: np.array, shape=(n_samples, n_features)
        label: np.array, shape=(n_samples,)
        outlier_ratio: float, ratio of outliers
        target_label: int, the label to be treated as normal
    """
    new_data = []
    new_label = []
    for i in range(10):
        if i != target_label:
            i_data = data[label==i]
            target_size = len(data[label==target_label])
            num = target_size*((outlier_ratio/9))
            idx = np.random.choice(list(range(len(i_data))),int(num),replace=False)
            new_data.append(i_data[idx])
            new_label.append(np.ones(len(idx))*i)
        else:
            new_data.append(data[label==i])
            new_label.append(np.ones(len(data[label==i]))*i)
    new_data = np.concatenate(new_data)
    new_label = np.concatenate(new_label)
    return new_data, new_label


class KNN:
    def __init__(self, train, test, train_label, test_label):
        self.train_data = train
        self.train_label = train_label
        self.test_data = test
        self.test_label = test_label
        self.anomaly_score = np.zeros(len(test_label))
        self.distance = pairwise_distances(self.test_data, self.train_data, metric='euclidean')

    def fit(self, k):
        self.k = k
        return

    def classifier(self):
        self.anomaly_score = np.mean(np.sort(self.distance)[:,:self.k], axis=1)
        return

    def score(self):
        return roc_auc_score(self.test_label, self.anomaly_score)

  
class KMeans:
    def __init__(self, train, test, train_label, test_label):
        self.train_data = train
        self.train_label = train_label
        self.test_data = test
        self.test_label = test_label
        self.anomaly_score = np.zeros(len(test_label))

    def fit(self, k):
        self.k = k
        index = np.random.choice(len(self.train_data), self.k, replace=False)
        self.centroids = np.array([self.train_data[index[i]] for i in range(self.k)])

        stop = False
        while not stop:
            stop = True
            dist = pairwise_distances(self.train_data, self.centroids, metric='euclidean')
            centroid_idx = np.argmin(dist, axis=1)

            # update centroid
            for i in np.unique(centroid_idx):
                new_centroid = np.mean(self.train_data[centroid_idx == i], axis=0)
                if not (new_centroid == self.centroids[i]).all():
                    self.centroids[i] = new_centroid
                    stop = False
        return

    def classifier(self):
        dist = pairwise_distances(self.test_data, self.centroids, metric='euclidean')
        self.anomaly_score = np.sort(dist)[:, 0]
        return

    def score(self):
        return roc_auc_score(self.test_label, self.anomaly_score)
    

class Distance_Based:
    def __init__(self, train, test, train_label, test_label):
        self.train_data = train
        self.train_label = train_label
        self.test_data = test
        self.test_label = test_label
        self.anomaly_score = np.zeros(len(test_label))

    def fit(self, k, function):
        self.k = k
        self.func = function
        return

    def Cos(self, p1, p2):
        return 1 - np.dot(p1, p2) / (np.linalg.norm(p1) * np.linalg.norm(p2))

    def L1(self, p1, p2):
        return np.sum(np.abs(p1 - p2))

    def L2(self, p1, p2):
        return np.sqrt(np.dot((p1 - p2), (p1 - p2).T))

    def L_inf(self, p1, p2):
        return np.max(np.abs(p1 - p2))

    def Mahalanobis(self, p1, p2):
        return np.sqrt(np.dot(np.dot((p1 - p2), self.cov_mat), (p1 - p2).T))

    def classifier(self):
        match self.func:
            case "Cosine":
                self.anomaly_score = np.sort(pairwise_distances(self.test_data, metric=self.Cos))[:, self.k]
            case "L1":
                self.anomaly_score = np.sort(pairwise_distances(self.test_data, metric=self.L1))[:, self.k]
            case "L2":
                self.anomaly_score = np.sort(pairwise_distances(self.test_data, metric=self.L2))[:, self.k]
            case "L_inf":
                self.anomaly_score = np.sort(pairwise_distances(self.test_data, metric=self.L_inf))[:, self.k]
            case "Mahalanobis":
                self.cov_mat = np.linalg.inv(np.cov(self.train_data, rowvar=False))
                self.anomaly_score = np.sort(pairwise_distances(self.test_data, metric=self.Mahalanobis))[:, self.k]
        return

    def score(self):
        return roc_auc_score(self.test_label, self.anomaly_score)
    

class LOF:
    def __init__(self, test, test_label):
        self.test_data = test
        self.test_label = test_label
        self.num = len(test_label)
        self.lof_score = np.zeros(self.num)

    def fit(self, k):
        self.k = k
        return

    def classifier(self):
        dist = pairwise_distances(test_data, metric='euclidean')
        k_dist_mat = np.outer(np.ones(self.num), np.sort(dist, axis=0)[self.k])
        reach_dist = np.maximum(dist, k_dist_mat)
        sort_index = np.argsort(dist, axis=1)[:,1:self.k+1]
        
        LRD = np.zeros(self.num)
        for i in range(self.num):
            LRD[i] = 1 / np.mean(reach_dist[i, sort_index[i]])

        for i in range(self.num):
            self.lof_score[i] = np.mean(LRD[sort_index[i]] / LRD[i])
        return

    def score(self):
        return roc_auc_score(self.test_label, self.lof_score)

    def visualization(self):
        data = TSNE().fit_transform(self.test_data)

        plt.figure(figsize=(16, 5))

        plt.subplot(121)
        plt.scatter(*(data.T), c = self.lof_score, cmap = 'viridis', s = 1.8)
        plt.colorbar()
        plt.title('predicted LOF score for normal digit=0')

        plt.subplot(122)
        scatter = plt.scatter(*(data.T), c = self.test_label, s = 1.8)
        plt.legend(handles=scatter.legend_elements()[0], labels=['normal', 'anomaly'])
        plt.title('ground truth label for normal digit=0')

        plt.savefig('tsne.png')
        plt.show()

        return
    

if __name__=="__main__":
    orig_train_data = torchvision.datasets.MNIST("MNIST/", train=True, transform=torchvision.transforms.Compose([torchvision.transforms.ToTensor()]),target_transform=None,download=True) #下載並匯入MNIST訓練資料
    orig_test_data = torchvision.datasets.MNIST("MNIST/", train=False, transform=torchvision.transforms.Compose([torchvision.transforms.ToTensor()]),target_transform=None,download=True) #下載並匯入MNIST測試資料

    orig_train_label = orig_train_data.targets.numpy()
    orig_train_data = orig_train_data.data.numpy()
    orig_train_data = orig_train_data.reshape(60000,28*28)

    orig_test_label = orig_test_data.targets.numpy()
    orig_test_data = orig_test_data.data.numpy()
    orig_test_data = orig_test_data.reshape(10000,28*28)

    # PCA
    from sklearn.decomposition import PCA
    pca = PCA(n_components=30)
    pca_data = pca.fit_transform(np.concatenate([orig_train_data,orig_test_data]))
    orig_train_data = pca_data[:len(orig_train_label)]
    orig_test_data = pca_data[len(orig_train_label):]

    orig_train_data,orig_train_label = resample_total(orig_train_data,orig_train_label,ratio=0.1)

    # Add
    list_of_k = [1, 5, 10]
    KNN_result = []
    KMeans_result = []
    Distance_result = []
    Density_result = []
    
    for i in tqdm.tqdm(range(10)):
        train_data = orig_train_data[orig_train_label==i]
        test_data,test_label = resample(orig_test_data,orig_test_label,target_label=i,outlier_ratio=0.1)

        # [TODO] prepare training/testing data with label==i labeled as 0, and others labeled as 1
        training_label = np.zeros(len(train_data))
        testing_label = np.where(test_label == i, 0, 1)

        # [TODO] implement methods
        # [TODO] record ROC-AUC for each method
        # Method.1: KNN_classifier
        record = []
        knn = KNN(train_data, test_data, training_label, testing_label)

        for k in [1, 5, 10]:
            knn.fit(k)
            knn.classifier()
            record.append(knn.score())

        KNN_result.append(record)

        # Method.2: KMeans_clustering
        record = []
        kmeans = KMeans(train_data, test_data, training_label, testing_label)

        for k in [1, 5, 10]:
            kmeans.fit(k)
            kmeans.classifier()
            record.append(kmeans.score())

        KMeans_result.append(record)

        # Method.3: Distance-Based AD
        record = []
        distance = Distance_Based(train_data, test_data, training_label, testing_label)

        # (a) Cosine Distance
        distance.fit(5, "Cosine")
        distance.classifier()
        record.append(distance.score())

        # (b) Minkowski Distance
        distance.fit(5, "L1")
        distance.classifier()
        record.append(distance.score())

        distance.fit(5, "L2")
        distance.classifier()
        record.append(distance.score())

        distance.fit(5, "L_inf")
        distance.classifier()
        record.append(distance.score())

        # (c) Mahalanobis Distance
        distance.fit(5, "Mahalanobis")
        distance.classifier()
        record.append(distance.score())

        Distance_result.append(record)

        # Method.4: Density-Based AD
        # (a) Local Outlier Factor
        record = []
        lof = LOF(test_data, testing_label)

        lof.fit(5)
        lof.classifier()
        record.append(lof.score())

        Density_result.append(record)

        # (b) Visualize with t-SNE
        if i == 0:
            lof.visualization()

    # [TODO] print the average ROC-AUC for each method
    print("\n")
    print("======result of KNN======")
    for i, v in enumerate(list(zip(*KNN_result))):
        print(f"K = {list_of_k[i]}: {sum(v)/10:.4f}")
    print("=========================\n")

    print("=====result of KMeans====")
    for i, v in enumerate(list(zip(*KMeans_result))):
        print(f"K = {list_of_k[i]}: {sum(v)/10:.4f}")
    print("=========================\n")

    list_of_dist_func = ["Cosine", "Minkowski(L1 norm)", "Minkowski(L2 norm)", "Minkowski(L-inf norm)", "Mahalanobis"]
    print("========result of Distance-Based========")
    for i, v in enumerate(list(zip(*Distance_result))):
        print(f"{list_of_dist_func[i]} distance: {sum(v)/10:.4f}")
    print("========================================\n")

    print("========result of Density-Based========")
    for v in list(zip(*Density_result)):
        print(f"Local Outlier Factor: {sum(v)/10:.4f}")
    print("========================================\n")