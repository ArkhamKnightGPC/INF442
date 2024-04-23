#include "ConfusionMatrix.hpp"
#include <iostream>

using namespace std;

ConfusionMatrix::ConfusionMatrix() {
    double** m_confusion_matrix = new double*[2];
    for(int i=0; i<2; i++){
        m_confusion_matrix[i] = new double[2];
        for(int j=0; j<2; j++){
            m_confusion_matrix[i][j] = 0;
        }
    }
}

ConfusionMatrix::~ConfusionMatrix() {
    // Attribute m_confusion_matrix is deleted automatically
}

void ConfusionMatrix::add_prediction(int true_label, int predicted_label) {
    m_confusion_matrix[true_label][predicted_label] += 1;
}

void ConfusionMatrix::print_evaluation() const{
    // Prints the confusion matrix
    cout << "\t\tPredicted\n";
    cout << "\t\t0\t1\n";
    cout << "Actual\t0\t"
        << get_tn() <<"\t"
        << get_fp() <<endl;
    cout <<"\t1\t"
        << get_fn() <<"\t"
        << get_tp() <<endl <<endl;
    // Prints the estimators
    cout << "Error rate\t\t"
        << error_rate() <<endl;
    cout << "False alarm rate\t"
        << false_alarm_rate() <<endl;
    cout << "Detection rate\t\t"
        << detection_rate() <<endl;
    cout << "F-score\t\t\t"
        << f_score() <<endl;
    cout << "Precision\t\t"
        << precision() <<endl;
}

int ConfusionMatrix::get_tp() const {//TRUE POSITIVE
    return m_confusion_matrix[1][1];
}

int ConfusionMatrix::get_tn() const {//TRUE NEGATIVE
   return m_confusion_matrix[0][0];
}

int ConfusionMatrix::get_fp() const {//FALSE POSITIVE: should be 0 but is 1
    return m_confusion_matrix[0][1];
}

int ConfusionMatrix::get_fn() const {//FALSE NEGATIVE: should be 1 but is 0
   return m_confusion_matrix[1][0];
}

double ConfusionMatrix::f_score() const {
    return (2.0*precision()*detection_rate())/(precision() + detection_rate());
}

double ConfusionMatrix::precision() const {
    double my_tp = get_tp();
    double my_fp = get_fp();
    if(my_tp + my_fp < 1e-9)return 0;
    return my_tp/(my_fp + my_tp);
}

double ConfusionMatrix::error_rate() const {
    return 1.0/(get_fn() + get_fp());
}

double ConfusionMatrix::detection_rate() const {
    double my_tp = get_tp();
    double my_fn = get_fp();
    if(my_tp + my_fn < 1e-9)return 0;
    return my_tp/(my_fn + my_tp);
}

double ConfusionMatrix::false_alarm_rate() const {
    double my_fp = get_tp();
    double my_tn = get_fp();
    if(my_fp + my_tn < 1e-9)return 0;
    return my_fp/(my_fp + my_tn);
}
