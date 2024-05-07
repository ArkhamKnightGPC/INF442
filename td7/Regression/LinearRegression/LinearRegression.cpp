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
	int n = m_dataset->get_nbr_samples();
    int dim = m_dataset->get_dim();

	Eigen::MatrixXd X = Eigen::MatrixXd(n, dim);//we add column of 1s but also exclude m_col_regr

    for(int i = 0; i < n; i++) {
		X(i, 0) = 1;//first column, always 1
        std::vector<double> row_i = m_dataset->get_instance(i);
		int cur_index = 1;
        for(int j = 0; j < dim; j++){
			if(j == m_col_regr)//we ignore column m_col_regr
				continue;
            X(i, cur_index) = row_i[j];
			cur_index++;//we use auxiliary index to keep track of next column
        }
    }

	return X;
}

Eigen::VectorXd LinearRegression::construct_y() {
	int n = m_dataset->get_nbr_samples();

	Eigen::VectorXd y = Eigen::VectorXd(n);

	for(int i = 0; i < n; i++) {
        std::vector<double> row_i = m_dataset->get_instance(i);
		y(i) = row_i[m_col_regr];
    }
	return y;
}

void LinearRegression::set_coefficients() {//constructor sets m_beta to null then calls this function
	Eigen::MatrixXd X = LinearRegression::construct_matrix();
	Eigen::VectorXd y = LinearRegression::construct_y();

	Eigen::VectorXd beta = (X.transpose() * X).ldlt().solve(X.transpose() * y);
    m_beta = new Eigen::VectorXd(beta);
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
	assert(dataset->get_dim() == m_dataset->get_dim());

	int n = dataset->get_nbr_samples();
	
	LinearRegression aux = LinearRegression(dataset, m_col_regr);
	Eigen::MatrixXd X = aux.construct_matrix();
	Eigen::VectorXd y = aux.construct_y();

	double avg = 0;
	for(int i=0; i<n; i++)
		avg += y(i);
	avg = avg/n;

	ess = 0;
	rss = 0;
	tss = 0;

	for(int i=0; i < n; i++){
		Eigen::VectorXd xi = X.transpose().col(i);
		double est_i = estimate(xi);
		tss += pow( y(i) - avg    	, 2);
		ess += pow( est_i - avg		, 2);
		rss += pow( est_i - y(i)	, 2);
	}

}

double LinearRegression::estimate(const Eigen::VectorXd & x) const {
	int dim = m_dataset->get_dim();
	double ans = (*m_beta)(0);
	for(int i=1; i<dim; i++){
		ans += (*m_beta)(i)*x(i-1);
	}
	return ans;
}
