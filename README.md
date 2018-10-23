# C++ implementation of KMeans
  
  K-Means is a very simple clustering algorithm (clustering belongs to unsupervised learning). Given a fixed number of clusters and an input dataset the algorithm tries to partition the data into clusters such that the clusters have high intra-class similarity and low inter-class similarity.

## Algorithm
  1. Initialize the cluster centers, either randomly within the range of the input data or (recommended) with some of the existing training examples  

  2. Until convergence  
    2.1. Assign each datapoint to the closest cluster. The distance between a point and cluster center is measured using the Euclidean distance.  
    2.2. Update the current estimates of the cluster centers by setting them to the mean of all instance belonging to that cluster

## Disadvantages of K-Means
  * The number of clusters has to be set in the beginning  
  * The results depend on the inital cluster centers  
  * It's sensitive to outliers  
  * It's not suitable for finding non-convex clusters  
  * It's not guaranteed to find a global optimum, so it can get stuck in a local minimum  


## C++ implementation
  [C++ code](https://github.com/ychen216/Kmeans/blob/master/Kmeans/main.cpp)
