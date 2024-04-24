#include<iostream>
#include<cassert>
#include "LinearRegression.hpp"
#include "Dataset.hpp"
#include "Regression.hpp"

LinearRegression::LinearRegression(Dataset* dataset, int col_regr) 
: Regression(dataset, col_regr) {
	m_beta = NULL;
	set_coefficients();
}

LinearRegression::~LinearRegression() {
	if (m_beta != NULL) {
		m_beta->resize(0);
		delete m_beta;
	}
}

Eigen::MatrixXd LinearRegression::construct_matrix() {
	// TODO Exercise 1

	// replace this command with what you compute as a matrix X
	return Eigen::MatrixXd(1, 1);
}

Eigen::VectorXd LinearRegression::construct_y() {
	// TODO Exercise 1

	// replace this command with what you compute as a vector y.
	return Eigen::VectorXd(1);
}

void LinearRegression::set_coefficients() {
	// TODO Exercise 2
}

const Eigen::VectorXd* LinearRegression::get_coefficients() const {
	if (!m_beta) {
		std::cout <<"Coefficients have not been allocated." <<std::endl;
		return NULL;
	}
	return m_beta;
}

void LinearRegression::show_coefficients() const {
	if (!m_beta) {
		std::cout << "Coefficients have not been allocated." <<std::endl;
		return;
	}
	
	if (m_beta->size() != m_dataset->get_dim()) {  // ( beta_0 beta_1 ... beta_{d} )
		std::cout << "Warning, unexpected size of coefficients vector: " << m_beta->size() << std::endl;
	}
	
	std::cout<< "beta = (";
	for (int i=0; i<m_beta->size(); i++) {
		std::cout << " " << (*m_beta)[i];
	}
	std::cout << " )" <<std::endl;
}

void LinearRegression::print_raw_coefficients() const {
	std::cout<< "{ ";
	for (int i = 0; i < m_beta->size() - 1; i++) {
		std::cout << (*m_beta)[i] << ", ";
	}
	std::cout << (*m_beta)[m_beta->size() - 1];
	std::cout << " }" << std::endl;
}

void LinearRegression::sum_of_squares(Dataset* dataset, double& ess, double& rss, double& tss) const {
	assert(dataset->get_dim()==m_dataset->get_dim());
	// TODO Exercise 4
}

double LinearRegression::estimate(const Eigen::VectorXd & x) const {
	// TODO Exercise 3
}
