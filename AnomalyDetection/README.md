# Anomaly Detection
###### tags: Python, Algorithms, Machine Learning
#### **2024 Spring/Summer**  *cr: tunyuanchang*

* **Anomaly Detection on MNIST**
    * Implement different anomaly detecting methods on MNIST dataset.
        * K Nearest Neighbor
        * Cluster-based (k-means clustering)
        * Distance-based (Cosine/Minkowski/Mahalanobis distance function)
        * Density-based (Local Outlier Factor detection algorithm)
        
* **Anomaly Detection for Time-Series Data**
    * Implement different anomaly detecting methods on timeseries dataset(Wafer. ECG200).
        * PCA Reconstruction
        * Discrete Fourier Transform
        * Discrete Haar Wavelet Transform
        
* **Deep Learning for Image Anomaly Detection**
    * Implement SimpleNet from scratch on MVTec dataset of 'leather' and 'metal nut' classes.
    * Ablation study on the MLP architectures of adapter and discriminator, and scale of Gaussian noise.
    
* **Deep Learning for Video Anomaly Detection**
    * Implement Jigsaw-VAD on avenue dataset
    * Implement and analyze three versions of temporal permutation prediction
        * matrix probability prediction
        * binary classification
        * multiclass classification
* **Improved TAnoGAN: Time Series Anomaly Detection with Generative Adversarial Networks**
    * Time-series anomaly detection
    * Implement improved model based on existing TAnoGAN with the following methods:
        * General performance metrics to handle manually threshold setting
        * Wasserstein Generative Adversarial Networks (WGANs) to deal with model instability and possibility of collapse mode
        * Model simplification/pruning to gain model efficiency with compatable performance
    * contributions: model performance improvements, stability, and efficiency