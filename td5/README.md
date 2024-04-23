# TD5: Density Estimation

## Overview

The goal of this TD(***travaux-dirigé***) is to implement three different kernel density estimators (**flat**, **gaussian** and **k-nn** kernels) under a common class structure using inheritance. The **mean shifts** clustering technique was also implemented and can be used to improve the quality of the estimators.

The folder is structured into separate compilation units, each in a different sub-folder:

- **kernel** containing the main code for the estimators
- **cloud** and **point** containing code from previous TDs
- **grading** with the test scripts
- **gradinglib** with the test library
- **quiz** with a python script used for preliminary analysis

In the root, we have the files:
- the file **main.cpp**, which is used for the tests script
- a **Makefile** that you can use to compile these tests

It also contains some subdirectories:

## How to run the tests

Compile using the Makefile and then run **grader** executable generated.

`make grader`

`./grader`
