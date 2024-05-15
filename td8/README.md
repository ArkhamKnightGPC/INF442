# TD8: Support Vector Machines

## Overview

The goal of this TD(***travaux-dirigé***) is to implement Soft Margin Kernel SVMs by solving the dual problem via a projected gradient ascent method.

The folder is structured into separate compilation units, each in a different sub-folder:

- **grading** with the test scripts
- **gradinglib** with the test library
- **quiz** with a python script used for the complementary quiz on Moodle
- **Dataset** with the dataset data structure as used in previous TDs
- **Kernel**  with implementations for linear, polynomial, rbf, sigmoid and rational-quadratic kernels
- **Svm** with the core SVM implementation

## How to run the tests

Compile using the Makefile and then run **grader** executable generated.

`make grader`

`./grader`
