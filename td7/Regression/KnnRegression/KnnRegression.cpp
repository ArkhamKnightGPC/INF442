#include <iostream>
#include <ANN/ANN.h>
#include "KnnRegression.hpp"

KnnRegression::KnnRegression(int k, Dataset* dataset, int col_regr)
: Regression(dataset, col_regr) {
	m_k = k;
 	// TODO Exercise 5
}

KnnRegression::~KnnRegression() {
	// TODO Exercise 5
}

double KnnRegression::estimate(const Eigen::VectorXd & x) const {
	assert(x.size()==m_dataset->get_dim()-1);
	// TODO Exercise 6
}

int KnnRegression::get_k() const {
	return m_k;
}

ANNkd_tree* KnnRegression::get_kdTree() const {
	return m_kdTree;
}
