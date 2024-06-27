
# Projects

## 2020 Fall/Winter
### Game with Allegro
###### C, C++
* 2D Plane Shooting Game
* Tower Defense Game

## 2021 Spring/Summer
### Alpha Othello
###### C++, Algorithms, AI
* Design and implement an AI that can play the boardgame Othello.

## 2021 Fall/Winter
### Essay Search Engine
###### C++, Algorithms, Data Structures
* Implement "Trie" to build data structure for searching.
* Top 10% performance in class competition.

### Logic Design Laboratory
###### Verilog, Finite State Machine, FPGA board

### Socket programming
###### Computer and Communications Networks
* TCP socket programming for both server and clients

## 2022 Spring/Summer
### Meet Deadline Requirements Challenge
###### C++, Multimedia, Networks, Algorithms
* Design congestion control algorithms to schedule the transmission for real time communication application.
* Won the first place performance in class competition.

### Assembly Coding
###### Assembly Code
* Implement KMP algorithms for string pattern matching.

## 2022 Fall/Winter
### Analysis of Street Recognition
###### Python, Machine Learning, CNN
* Build a CNN model to recognize cities from Google Street View images.
* Visualize and analyze the features that machine focus on.
### Machine Learning
###### Python, Mcchine Learning
* **Dengue Case Prediction**
  * Implement "Gradient Descent" for linear regression from scratch.
  * Build the model to predict the number of dengue cases of three cities with self-built regression model. (Regression)
* **Diabetes Prediction**
  * Implement "Decision Tree" and "Random Forest" for classification from scratch.
  * Build the model to predict whether the patients have diabetes or not with self-built random forest classifier. (Binary classification)
  * Adopt the methods of undersampling for imbalanced data and fisher score for feature selection to improve performance of model.
* **Neural Network**
  * Implement "Neural Network" (including Dense layer and Activation layer[Sigmoid, Softmax, ReLU function]) from scratch.
  * Build the model with optimization algorithm of batch gradient to determine whether breast cancer is malignant or benign with self-built neural network. (Binary classification)
  * Build the model with optimization algorithm of mini-batch gradient to classify MNIST handwritten digits with self-built neural network. (Multi-class classification)
* **Convolutional Neural Network**
  * Implemnt "Convolutional Neural Network" (including Convolution layer and Maxpooling layer) from scratch on the basis of Neural Network above.
  * Build the model with optimization algorithm of mini-batch gradient descent to determine whether a CXR image is normal or not. (Binary classification)
* **EEG Signal Classification**
  * Build RNN-based(LSTM) and CNN-based(EEGNet) models to predict motor imagery class based on the given EEG data(brain signal). (Multi-class classification)

### Trading Valley Strategy Design
###### Python, Machine Learning
* Design a strategy which makes the maximum profit and high sharp ratio for US stock trading.

### Operating System
###### NachOS
* System Call
* Multi-Programming
* CPU Scheduling
* File System
* Pthreads

## 2023 Spring/Summer
### Data Science
###### Python, Machine Learning, Algorithms
* **Frequent Patterns**
    * Implenment "FP-Growth" from scratch to find freqent patterns with support in transactions.
* **Supervised Binary Classification Problem with Machine Learning**
    * Implenment random forest classifier with feature engineering.
    * Including categorical encoding, date and time engineering, outlier engineering and missing data imputation.
    * Adopt the methods of oversampling for imbalanced data to improve performance of model.
* **Node Classification with Graph Neural Network**
    * Implement GNN for node classification on PubMed dataset.
    * Test the learning ability of graph neural network with lack of labeled data. (take structural information into account)
* **Image Classification with Horizontal Federated Learning**
    * Implement both server and user base for horizontal federated learning with FedAvg algorithms on CIFAR10 dataset.
    * Discussion:
        * data distribution v.s. global model accuracy
        * number of users in a round v.s. global model accuracy and global model convergence speed

* **Node Misclassification with Graph Adversarial Attack**
    * Implement Nettack algorithms for graph adversarial attack on Cora citation network dataset.
* **Paper Presentation**
    * selected paper: Attention, Please! Adversarial Defense via Activation Rectification and Preservation [Adversarial Attacks]

### Analysis of Trend in Taiwan Stock Market
###### Python, Machine Learning, Pattern Recognition
* Implement methods of regression and classification to predict the rise or fall of TWSE.
* Improve the performance with Recurrent Neural Network.

### Embedded System
###### AVR programmimg(avr-gcc, Arduino IDE), Raspberry Pi
* Timer
* MIDI Music
* Board-to-board Communication (UART, I^2^C)
* ADC (Analog-to-Digital Converter)
* Power Management and Sleep Modes
* Multi-Threads
* Synchronization (Protection of Critical Section with Mutex Lock & Semaphore)

## 2023 Fall/Winter
### Parallel Programming
###### C++, CUDA, UCX
* **Odd-Even Sort**
    * Implement MPI version.
    * Parallelize the sorting with "Odd-Even Sort" algorithm.

* **Mandelbrot Set**
    * Implement pthread and hybrid(MPI + OpenMP) versions.
    * Parallelize the calculation of "Mandelbrot Set".
    
* **All-Pairs Shortest Path**
    * Implement CPU(pthread), single-GPU(CUDA) and multi-GPU(CUDA + OpenMP) versions.
    * Parallelize the calculation of APSP with "Blocked Floyd-Warshall" algorithm.
    
* **Observe the behavior of UCX**
    * Learn the UCX framework and program structure.
* **Linear Regression with RANSAC**
    * Implement OpenMP, CUDA and OpenACC versions.
    * Performance comparison of different parallel methods.

## 2024 Spring/Summer
### Machine Learning for Anomaly Detection
###### Python, Machine Learning
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
