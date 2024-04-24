# TD7: kNN for regression

## Overview

The goal of this TD(***travaux-dirigé***) is to implement a linear regression algorithm as well as the kNN algorithm for regression.

The folder is structured into separate compilation units, each in a different sub-folder:

- **include** contaning the [Eigen](https://eigen.tuxfamily.org/) and [ANN](https://www.cs.umd.edu/users/mount/ANN/) C++ libraries.
- **grading** with the test scripts
- **gradinglib** with the test library
- **quiz** with a python script used for preliminary analysis
- **regression** containing the Regression abstract class and the implementation for each regressor.

## How to run the tests

Compile using the Makefile and then run **grader** executable generated.

`make grader`

`./grader`
