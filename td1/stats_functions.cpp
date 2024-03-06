// Include the library that defines input/output streams and operations on them
#include <iostream>
// Include the library with basic mathematical functions, e.g. sqrt
#include <cmath>
// Need that for memset
#include <cstring>

/********************
 * Helper functions *
 ********************/

// Read the data matrix from the standard input
void read_matrix (double** matrix, int rows, int columns) {
    for (int i = 0; i < rows; ++i) {
        matrix[i] = new double[columns];
        for (int j = 0; j < columns; ++j)
            std::cin >> matrix[i][j];
    }
}

// Print an array on the standard output
void print_array (double values[], int length) {
    for (int i = 0; i < length - 1; i++)
        std::cout << values[i] << " ";

    std::cout << values[length - 1];
}

// Prepare an empty matrix
double** prepare_matrix(int rows, int columns) {
    double** matrix = new double* [rows];
    for (int i = 0; i < rows; ++i) {
        matrix[i] = new double[columns];
        for (int j = 0; j < columns; ++j)
            matrix[i][j] = 0;
    }

    return matrix;
}

/*****************************************************
 * Exercise 1: Mean, variance and standard deviation *
 *****************************************************/

/** 
 * This function computes the mean of the given array of values 
 * 
 * @param values the array with the values
 * @param length the length of the array 'values'
 * @return the mean of the values in the array
 */
double compute_mean (double values[], int length) {
    double sum = 0;

    for(int i=0; i<length; i++)
        sum += values[i];

    return sum / length;
}

/** 
 * This function computes the variance of the given array of values 
 * 
 * @param values the array with the values
 * @param length the length of the array 'values'
 * @return the variance of the values in the array
 */
double compute_variance (double values[], int length) {
    double mean, sum_sq, exp_sq, var;

    mean = compute_mean(values, length);
    
    sum_sq = 0; //compute expected value of x^2
    for(int i=0; i<length; i++){
        sum_sq += values[i]*values[i];
    }
    exp_sq = sum_sq/length;
    var = exp_sq - mean*mean; //variance = Exp(x^2) - Exp(x)^2

    return var;
}


/** 
 * This function computes the unbiased sample variance of the given
 * array of values 
 * 
 * @param values the array with the values
 * @param length the length of the array values
 * @return the variance of the values in the array
 */
double compute_sample_variance (double values[], int length) {
    double mean, sample_variance;

    mean = compute_mean(values, length);

    sample_variance = 0;
    for(int i=0; i<length; i++)
        sample_variance += (values[i] - mean)*(values[i] - mean);
    sample_variance = sample_variance/(length - 1);

    return sample_variance;
}

/** 
 * This function computes the standard deviation of the given
 * array of values 
 * 
 * @param values the array with the values
 * @param length the length of the array values
 * @return the variance of the values in the array
 */
double compute_standard_deviation (double values[], int length) {
    double variance = compute_variance(values, length);

    return sqrt(variance);
}

/** 
 * This function computes the unbiased sample standard deviation
 * of the given array of values 
 * 
 * @param values the array with the values
 * @param length the length of the array values
 * @return the variance of the values in the array
 */
double compute_sample_standard_deviation (double values[], int length) {
    double sample_variance = compute_sample_variance(values, length);

    return sqrt(sample_variance);
}

/*************************************
 * Exercise 2: Working with matrices *
 *************************************/

/**
 * This function prints a rectangular matrix on the standard output, 
 * placing each row on a separate line.  
 * 
 * @param matrix the matrix to print
 * @param rows the number of rows in the matrix
 * @param columns the number of columns
 */
void print_matrix (double** matrix, int rows, int columns) {

    for(int i=0; i<rows; i++){
        for(int j=0; j<columns; j++){

            //single whitespace between consecutive entries
            if(j > 0)std::cout << " ";

            std::cout << matrix[i][j];
        }
        std::cout << "\n";
    }

}

/** 
 * This function extracts one row from a data matrix
 * 
 * @param matrix the matrix with the data
 * @param columns the number of columns in the matrix
 * @param index the index of the row to extract
 * @param row the array where the extracted values are to be placed
 */
void get_row (double** matrix, int columns, int index, double row[]) {
    for(int j=0; j<columns; j++)
        row[j] = matrix[index][j];
}

/** 
 * This function extracts one column from a data matrix
 * 
 * @param matrix the matrix with the data
 * @param rows the number of rows in the matrix
 * @param index the index of the column to extract
 * @param column the array where the extracted values are to be placed
 */
void get_column (double** matrix, int rows, int index, double column[]) {
    for(int i=0; i<rows; i++)
        column[i] = matrix[i][index];
}

/****************************************************
 * Exercise 3: Covariance and correlation of arrays *
 ****************************************************/

/**
 * This function computes the covariance of two vectors of data of the same length
 * @param values1 the first vector
 * @param values2 the second vector
 * @param length the length of the two vectors
 * @return the covariance of the two vectors
 */
double compute_covariance(double values1[], double values2[], int length) {
    double covariance, mean1, mean2;

    covariance = 0;
    mean1 = compute_mean(values1, length);
    mean2 = compute_mean(values2, length);

    for(int i=0; i<length; i++)
        covariance += (values1[i] - mean1)*(values2[i] - mean2);
    covariance /= length;

    return covariance;
}

/**
 * This function computes the correlation of two vectors of data of the same length
 * 
 * @param values1 the first vector
 * @param values2 the second vector
 * @param length the length of the two vectors
 * @return the correlation of the two vectors
 */
double compute_correlation(double values1[], double values2[], int length) {
    double covariance, std1, std2, correlation;

    covariance = compute_covariance(values1, values2, length);
    std1 = compute_standard_deviation(values1, length);
    std2 = compute_standard_deviation(values2, length);

    correlation = covariance/(std1*std2);
    return correlation;
}

/***************************************************
 * Exercise 4: Covariance and correlation matrices *
 ***************************************************/

/**
 * This function computes the covariance matrix of the matrix provided as argument
 * 
 * @param data_matrix the input matrix 
 * @param rows the number of rows in the matrix
 * @param columns the number of columns in the matrix
 * @return the covariance matrix
 */
double** compute_covariance_matrix (double** data_matrix, int rows, int columns) {
    // Initialise a square matrix
    double** matrix = prepare_matrix(columns, columns);
    // Prepare temporary storage for columns
    double column1[rows], column2[rows];

    for(int i=0; i<columns; i++){

        get_column(data_matrix, rows, i, column1);//get x_i

        for(int j=0; j<columns; j++){
            if(i==j){//we compute var(x_i)
                matrix[i][j] = compute_variance(column1, rows);
            }else{//we compute cov(x_i, x_j)
                get_column(data_matrix, rows, j, column2);//get x_j
                matrix[i][j] = compute_covariance(column1, column2, rows);
            }
        }
    }

    return matrix;
}

/**
 * This function computes the correlation matrix of the matrix provided as argument
 * 
 * @param data_matrix the input matrix 
 * @param rows the number of rows in the matrix
 * @param columns the number of columns in the matrix
 * @return the correlation matrix
 */
double** compute_correlation_matrix (double** data_matrix, int rows, int columns) {
    // Initialise a square matrix
    double** matrix = prepare_matrix(columns, columns);
    // Prepare temporary storage for columns
    double column1[rows], column2[rows];

    for(int i=0; i<columns; i++){

        get_column(data_matrix, rows, i, column1);//get x_i

        for(int j=0; j<columns; j++){
            get_column(data_matrix, rows, j, column2);//get x_j
            matrix[i][j] = compute_correlation(column1, column2, rows);
        }
    }

    return matrix;
}
