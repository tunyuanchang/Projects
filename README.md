
# Projects
###### cr: tunyuanchang

## 2020 Fall/Winter
### Game with Allegro
###### C, C++
* 2D Plane Shooting Game
* Tower Defense Game

## 2021 Spring/Summer
### Alpha Othello
###### C++, Algorithms, AI
* Design and implement an AI that can play the boardgame Othello.
* Enhance AI policy through the following methods:
    * Tree search algorithms (e.g. Minimax, Alpha-Beta Pruning): to effectively determine the next move
    * State-action value function design: to evaluate the score of the board

## 2021 Fall/Winter
### Essay Search Engine
###### C++, Algorithms, Data Structures
* Develop a simple search engine that can efficiently search through a set of essay files based on various queries.
* Support exact matches, prefix searches, suffix searches, and utilize "and/or" operators.
* Implement "Trie" to build data structure for processing query files to execute searches and parsing essay files to generate outputs.
* Top 10% performance in class competition.

### Logic Design Laboratory
###### Verilog, Finite State Machine, FPGA board

### Socket programming
###### Computer and Communications Networks
* TCP socket programming for both server and clients

## 2022 Spring/Summer
### Meet Deadline Requirements Challenge (MM’21 Grand Challenge)
###### C++, Multimedia, Networks, Algorithms
* Design congestion control algorithms to schedule the transmission for real time communication application.
* Implement a transmission scheduler to manage block sending sequences within bandwidth constraints by developing a formula that incorporates priorities, deadlines, and block sizes.
* Implement Reinforcement Learning (RL) to optimize bandwidth usage and prevent packet loss in dynamically changing network conditions by utilizing a congestion window and adjusting the sending rate.
* Won the first place performance in class competition.

### Assembly Coding
###### Assembly Code
* Implement KMP algorithms for string pattern matching.

## 2022 Fall/Winter
### Analysis of Street Recognition
###### Python, Machine Learning, CNN
* Explore the similarities and differences between how machines and human recognize street view images.
* Develop CNN models to identify cities from Google Street View images, utilizing self-built CNNs, ResNet, DenseNet, and Xception architectures.
* Visualize and analyze the features that the models focus on using Grad-CAM.
* Conduct experiments to improve performance based on visualization analysis:
    * Crop images: to eliminate the effects of mosaic/pixalation
    * Apply Canny edge detector: to mitigate the impact of lighting issues, such as blurring

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
    [citation] Wu, Shangxi, et al. "Attention, please! adversarial defense via activation rectification and preservation." ACM Transactions on Multimedia Computing, Communications and Applications 19.4 (2023): 1-18.

### Analysis of Trend in Taiwan Stock Market
###### Python, Machine Learning, Pattern Recognition
* Implement methods of regression and classification to predict the rise or fall of TWSE.
* Improve the performance with Recurrent Neural Network (RNN).

<!--
### Embedded System
###### AVR programmimg(avr-gcc, Arduino IDE), Raspberry Pi
* Timer
* MIDI Music
* Board-to-board Communication (UART, I^2^C)
* ADC (Analog-to-Digital Converter)
* Power Management and Sleep Modes
* Multi-Threads
* Synchronization (Protection of Critical Section with Mutex Lock & Semaphore)
-->

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

* **Pixels in Circle**
    * Parallelize the approximate calculation. 
    * Implement MPI, pthread, OpenMP and hybrid(MPI + OpenMP) versions.

* **Edge Detection**
    * Parallelize the convolution calculation of Sobel operator.
    * Optimize with Coalesced Memory Access, Lower Precision and Shared Memory.

* **DNN Model**
    * Parallelize the linear function and activation function of DNN Model.
    * Implement OpenACC version.

* **Linear Regression with RANSAC**
    * Implement OpenMP, CUDA and OpenACC versions.
    * Performance comparison of different parallel methods.

## 2024 Spring/Summer
### Machine Learning for Anomaly Detection
###### Python, Machine Learning
* **Anomaly Detection on MNIST**
    * Implement different anomaly detecting methods on MNIST dataset.
        * K-Nearest Neighbor
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
    * Implement Jigsaw-VAD on avenue dataset.
    * Implement and analyze three versions of temporal permutation prediction
        * matrix probability prediction
        * binary classification
        * multiclass classification

* **Improved TAnoGAN: Time Series Anomaly Detection with Generative Adversarial Networks**
    * Time-series anomaly detection
    * Implement improved model based on existing TAnoGAN with the following methods:
        * General performance metrics to handle manually threshold setting.
        * Wasserstein Generative Adversarial Networks (WGANs) to deal with model instability and possibility of collapse mode.
        * Model simplification/pruning to gain model efficiency with compatable performance.
    * contributions: model performance improvements, stability, and efficiency

## 2024 Fall/Winter
### Natural Language Processing
###### Python, Machine Learning



## Undergraduate Project
### Recommendation System with Graph Neural Network
###### Graph Neural Network, Recommendation System
Advisor: Chih-Ya, Shen
* Focus on “Graph-Based Collaborative Filtering”
* Study and analyze two architectural frameworks: 
    * Neural Graph Collaborative Filtering (NGCF)
    * Fast Incremental Recommendation (FIRE)
* Enhance the performance of FIRE by two approaches
    * Apply different time attenuations
    * Apply time windowing

