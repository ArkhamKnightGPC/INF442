# TD5: kNN for classification

## Overview

The goal of this TD(***travaux-dirigé***) is to 

The folder is structured into separate compilation units, each in a different sub-folder:

- **include** contaning the [Eigen](https://eigen.tuxfamily.org/) and [ANN](https://www.cs.umd.edu/users/mount/ANN/) C++ libraries.
- **grading** with the test scripts
- **gradinglib** with the test library
- **quiz** with a python script used for preliminary analysis

In the root, we have the files:
- the file **Classification.cpp**,
- the file **ConfusionMatrix.cpp**,
- the file **Dataset.cpp**,
- the file **KnnClassification.cpp**,
- the file **RandomProjection.cpp**,
- the file **main.cpp**, which calls upon the other test files
- a **Makefile** that you can use to compile these tests

It also contains some subdirectories:

## How to run the tests

Compile using the Makefile and then run **grader** executable generated.

`make grader`

`./grader`
