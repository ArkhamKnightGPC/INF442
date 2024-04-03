#include <cmath> // for pow, atan, should you need them
#include <iostream> // for cerr

#include <point.hpp>
#include <cloud.hpp>
#include <gaussian.hpp>

double gaussian::volume() const {
	double d = data->get_point(0).get_dim();
	return pow(2*M_PI, d/2.0);
}

double gaussian::profile(double t) const {
	return std::exp(-t/2.0);
}

void gaussian::guess_bandwidth() {
	double n = data->get_n();
	bandwidth = 1.06*data->standard_deviation()/pow(n, 1.0/5.0);
}
