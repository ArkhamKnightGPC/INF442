#include <cmath> // for pow, atan, should you need them

#include <point.hpp>
#include <flat.hpp>

double flat::volume() const {
	double aux = data->get_point(0).get_dim()/2.0;
	return pow(M_PI, aux)/std::tgamma(aux + 1);
}

double flat::profile(double t) const {
	//return 1 if and only if t≤1 and 0 otherwise
	return 1 ? (t <= 1) : 0;
}
