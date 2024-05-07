#include <iostream>
#include <ANN/ANN.h>
#include "KnnRegression.hpp"

KnnRegression::KnnRegression(int k, Dataset* dataset, int col_regr)
: Regression(dataset, col_regr) {
	m_k = k;

 	int n = m_dataset->get_nbr_samples();
    int dim = m_dataset->get_dim()-1;

    double** pa = new double*[n];
    for(int i = 0; i < n; i++) {
        pa[i] = new double[dim];
        std::vector<double> point_i = dataset->get_instance(i);

		int cnt = 0;
        for(int j = 0; j < dim+1; j++){
			if(j == col_regr)
				continue;
            pa[i][cnt] = point_i[j];
			cnt++;
        }
    }

    m_kdTree = new ANNkd_tree(
                            pa, // data point array
                            n, // number of points
                            dim); //dimension

    m_dataPts = pa;
}

KnnRegression::~KnnRegression() {
	delete m_kdTree;
    for(int i = 0; i < m_dataset->get_nbr_samples(); i++) {
        delete[] m_dataPts[i];
    }
    delete[] m_dataPts;
}

double KnnRegression::estimate(const Eigen::VectorXd & x) const {

	assert(x.size() == m_dataset->get_dim()-1);

	int n = m_dataset->get_nbr_samples();
    int dim = m_dataset->get_dim() - 1;

	ANNpoint pt = new ANNcoord[dim];
	for(int i=0; i < dim; i++){
		pt[i] = x(i);
	}
	
	double avg = 0; //average out of k neighbors
    ANNidxArray nn_idx = new ANNidx[m_k];
    ANNdistArray dists = new ANNdist[m_k];

    //find k nearest neighbors
    m_kdTree->annkSearch(pt, m_k, nn_idx, dists);

    for (int i = 0; i < m_k; i++) {
        int idx = nn_idx[i];
		std::vector<double> point_i = m_dataset->get_instance(idx);
        double vote = point_i[m_col_regr];
        avg += vote;
    }

	avg = avg/m_k;

    delete[] nn_idx;
    delete[] dists;
    delete[] pt;

    return avg;
}

int KnnRegression::get_k() const {
	return m_k;
}

ANNkd_tree* KnnRegression::get_kdTree() const {
	return m_kdTree;
}
