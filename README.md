# INF442

This repository contains lab assignments from the ***Data Analysis in C++*** course at École polytechnique.

For each assignment a detailed ***README*** file is provided with instructions to compile and execute the code.

## Lab assignments

- TD1: Basic statistics in C++

The goal of this TD(***travaux-dirigé***) is to compute basic statistics(**standard deviation, covariance, correlation**) for variables in a ***.csv*** dataset. 

- TD2: K-Dimensional Tree (kd-tree)

The goal of this TD(***travaux-dirigé***) is to implement the **kd-tree** data structure to solve the **k-nearest neighbor** problem. For querying, we consider both the **defeatist** and **backtracking** approaches and compare their performances.

- TD3: K-Means

The goal of this TD(***travaux-dirigé***) is to implement the **k-means** algorithm for data classification using **Voronoi partitions** and **Lloyd's algorithm**. Three different initialization strategies where implemented: **random partition**, **forgy** and **k-means++**.

- TD4: Hierarchical Clustering

The goal of this TD(***travaux-dirigé***) is to implement an **agglomerative hierarchical clustering** algorithm based on **single-linkage** using the **union-find** data structure. We use dendrograms for visualisation of the clustering process.

- TD5: Density Estimation

The goal of this TD(***travaux-dirigé***) is to implement three different kernel density estimators (**flat**, **gaussian** and **k-nn** kernels) under a common class structure using inheritance. The **mean shifts** clustering technique was also implemented and can be used to improve the quality of the estimators.

- TD6: kNN for classification

The goal of this TD(***travaux-dirigé***) is to implement the kNN classification algorithm. We also built a Confusion matrix class to analyse key prediction metrics. The [Eigen](https://eigen.tuxfamily.org/) and [ANN](https://www.cs.umd.edu/users/mount/ANN/) C++ libraries are used for implementation.

- TD7: kNN for regression

The goal of this TD(***travaux-dirigé***) is to implement a linear regression algorithm as well as the kNN algorithm for regression. The [Eigen](https://eigen.tuxfamily.org/) and [ANN](https://www.cs.umd.edu/users/mount/ANN/) C++ libraries are used for implementation.

- TD8: Support Vector Machines

The goal of this TD(***travaux-dirigé***) is to implement Soft Margin Kernel SVMs by solving the dual problem via a projected gradient ascent method.
