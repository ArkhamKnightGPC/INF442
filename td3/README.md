# TD3: K-means

## Overview

The goal of this TD(***travaux-dirigé***) is to implement the **k-means** algorithm for data classification using **Voronoi partitions** and **Lloyd's algorithm**. Three different initialization strategies where implemented: **random partition**, **forgy** and **k-means++**.

The folder contains the following files:

- the source file **kmeans.cpp** which contains the main code
- the file **main.cpp**, which is used for the tests script
- a **Makefile** that you can use to compile these tests

It also contains some subdirectories:

- **csv** with the main dataset
- **grading** with the test scripts
- **gradinglib** with the test library
- **quiz** with a **Jupyter notebook** file for preliminary analysis, parameters can be modified to observe different plots.

## How to run the tests

Compile using the Makefile and then run **grader** executable generated.

`make grader`

`./grader`

