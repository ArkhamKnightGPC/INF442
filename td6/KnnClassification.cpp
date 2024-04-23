
#include "KnnClassification.hpp"
#include <iostream>
#include <ANN/ANN.h>


KnnClassification::KnnClassification(int k, Dataset *dataset, int col_class)
    : Classification(dataset, col_class) {

    int n = dataset->get_n_samples();
    int dim = dataset->get_dim() - 1;

    double** pa = new double*[n];
    for(int i = 0; i < n; i++) {
        pa[i] = new double[dim];
        std::vector<double> point_i = dataset->get_instance(i);
        for(int j = 0; j < dim; j++){
            pa[i][j] = point_i[j+1];
        }
    }

    m_k = k;
    m_col_class = col_class;
    m_dataset = dataset;

    m_kd_tree = new ANNkd_tree(
                            pa, // data point array
                            n, // number of points
                            dim); //dimension

    m_data_pts = pa;
}

KnnClassification::~KnnClassification() {
    delete m_kd_tree;
    for(int i = 0; i < m_dataset->get_n_samples(); i++) {
        delete[] m_data_pts[i];
    }
    delete[] m_data_pts;
}

int KnnClassification::estimate(const ANNpoint &x, double threshold) const {

    int* votes = new int[m_k](); //store vote of each neighbor
    ANNidxArray nn_idx = new ANNidx[m_k];
    ANNdistArray dists = new ANNdist[m_k];

    //find k nearest neighbors
    m_kd_tree->annkSearch(x, m_k, nn_idx, dists);

    for (int i = 0; i < m_k; i++) {
        int idx = nn_idx[i];
        int vote = m_dataset->get_instance(idx)[m_col_class];
        votes[vote]++;
    }

    int max_votes = 1;
    int prediction = -1;
    for (int i = 0; i < m_k; i++) {
        if (votes[i] > max_votes) {
            max_votes = votes[i];
            prediction = i;
        }
    }

    delete[] nn_idx;
    delete[] dists;
    delete[] votes;

    return prediction;
}

int KnnClassification::get_k() const {
    return m_k;
}

ANNkd_tree *KnnClassification::get_kd_tree() {
    return m_kd_tree;
}

const ANNpointArray KnnClassification::get_points() const {
    return m_data_pts;
}
