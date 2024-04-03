#include <point.hpp>
#include <cloud.hpp>
#include <kernel.hpp>
#include <knn.hpp>

// TODO 2.2.1: implement density for knn kernel
knn::knn(cloud* data_, int k_, double V_) : kernel(data_), k(k_), V(V_) {}

double knn::density(const point& p) const {
    double n = data->get_n();
    double volume = this->volume();
    double dk = data->k_dist_knn(p, k);

    return ((double)k)/(2.0*n*volume*dk);
}

double knn::volume() const {
    return V;
}
