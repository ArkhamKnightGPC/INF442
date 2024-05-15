#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <numeric>
#include <algorithm>

#include "Kernel.hpp"
#include "ConfusionMatrix.hpp"
#include "Svm.hpp"

SVM::SVM(Dataset* dataset, int col_class, Kernel K):
    col_class(col_class), kernel(K) {

    int n = dataset->get_nbr_samples();
    int dim = dataset->get_dim() - 1;

    train_labels = std::vector<int>(n);
    train_features = std::vector<std::vector<double>>(n, std::vector<double>(dim));

    // Exercise 2: put the correct columns of dataset in train_labels and _features AGAIN!
    // BEWARE: transform 0/1 labels to -1/1
    for(int i=0; i<n; i++){
        std::vector<double> row_i = dataset->get_instance(i);
        train_labels[i] = 2*row_i[col_class]-1;
        int aux = 0, aux2 = 0;
        for(auto it : row_i){
            if(aux2 != col_class){
                train_features[i][aux] = row_i[aux2];
                aux++;
            }
            aux2++;
        }
    }

    compute_kernel();
}

SVM::~SVM() {
}

void SVM::compute_kernel() {
    const int n = train_features.size();
    alpha = std::vector<double>(n);
    computed_kernel = std::vector<std::vector<double>>(n, std::vector<double>(n));

    // Exercise 2: put y_i y_j k(x_i, x_j) in the (i, j)th coordinate of computed_kernel
    for(int i=0; i<n; i++){
        std::vector<double> row_i = train_features[i];
        for(int j=0; j<n; j++){
            std::vector<double> row_j = train_features[j];
            computed_kernel[i][j] = train_labels[i]*train_labels[j]*kernel.k(row_i, row_j);
        }
    }
}

void SVM::compute_beta_0(double C) {

    // count keeps track of the number of support vectors (denoted by n_s)
    int count = 0;

    beta_0 = 0.0;
    // Exercise 3
    // Use clipping_epsilon < alpha < C - clipping_epsilon instead of 0 < alpha < C
    const int n = train_features.size();
    for(int i=0; i<n; i++){
        if(clipping_epsilon < alpha[i] && alpha[i] < C-clipping_epsilon){
            count++;
            std::vector<double> row_i = train_features[i];
            for(int j=0; j<n; j++){
                std::vector<double> row_j = train_features[j];
                beta_0 += alpha[j]*train_labels[j]*kernel.k(row_i, row_j);
            }
            beta_0 -= train_labels[i];
        }
    }

    // This performs 1/n_s
    beta_0 /= count;
}

void SVM::train(const double C, const double lr) {
    const int n = train_features.size();
    // Exercise 4
    // Perform projected gradient ascent
    // While some alpha is not clipped AND its gradient is above stopping_criterion

    // (1) Set stop = false
    bool stop = false;

    // (2) While not stop do
    while(!stop){
        // (2.1) Set stop = true
        stop = true;

        // (2.2) For i = 1 to n do
        for(int i=0; i<n; i++){

            // (2.2.1) Compute the gradient - HINT: make good use of computed_kernel
            double gradient = 1;
            for(int j=0; j<n; j++)
                gradient -= alpha[j]*computed_kernel[i][j];

            // (2.2.2) Move alpha in the direction of the gradient
            // eta corresponds to lr (for learning rate)
            alpha[i] = alpha[i] + lr*gradient;
            bool clipping_not_necessary = (clipping_epsilon < alpha[i] && alpha[i] < C-clipping_epsilon);

            // (2.2.3) Project alpha in the constraint box by clipping it
            alpha[i] = std::max(0.0, std::min(C, alpha[i]));

            // (2.2.4) Adjust stop if necessary
            //If clipping was not necessary and |gradient| > stopping_criterion   then   stop=false
            if(clipping_not_necessary && std::abs(gradient) > stopping_criterion){
                stop = false;
            }
        }
    }

    // (3) Compute beta_0
    compute_beta_0(C);
}

double signe(double x){
    double eps = 1e-9;
    if(x > eps)return 1;
    if(x < -eps)return -1;
    return 0;
}

int SVM::f_hat(const std::vector<double> x) {
    double aux = 0;
    const int n = train_features.size();

    for(int i=0; i<n; i++){
        aux += alpha[i]*train_labels[i]*kernel.k(train_features[i], x);
    }

    aux -= beta_0;
    return signe(aux);
}

ConfusionMatrix SVM::test(const Dataset* test) {
    int n = test->get_nbr_samples();
    int dim = test->get_dim() - 1;
    // Collect test_features and test_labels and compute confusion matrix
    std::vector<double> test_labels (n);
    std::vector<std::vector<double>> test_features (n, std::vector<double>(dim));
    ConfusionMatrix cm;

    // Exercise 6
    // Put test dataset in features and labels
    // Use f_hat to predict and put into the confusion matrix
    // BEWARE: transform -1/1 prediction to 0/1 label
    for(int i=0; i<n; i++){
        std::vector<double> row_i = test->get_instance(i);
        test_labels[i] = row_i[col_class];
        int aux = 0, aux2 = 0;
        for(auto it : row_i){
            if(aux2 != col_class){
                test_features[i][aux] = row_i[aux2];
                aux++;
            }
            aux2++;
        }
        double pred = f_hat(test_features[i]);
        cm.add_prediction(test_labels[i], (pred+1)/2);
    }

    return cm;
}

int SVM::get_col_class() const {
    return col_class;
}

Kernel SVM::get_kernel() const {
    return kernel;
}

std::vector<int> SVM::get_train_labels() const {
    return train_labels;
}

std::vector<std::vector<double>> SVM::get_train_features() const {
    return train_features;
}

std::vector<std::vector<double>> SVM::get_computed_kernel() const {
    return computed_kernel;
}

std::vector<double> SVM::get_alphas() const {
    return alpha;
}

double SVM::get_beta_0() const {
    return beta_0;
}

void SVM::set_alphas(std::vector<double> alpha) {
    this->alpha = alpha;
}
