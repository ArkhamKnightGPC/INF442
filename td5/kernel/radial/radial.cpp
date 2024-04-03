#include <cmath> // for pow, should you need it

#include <point.hpp>
#include <cloud.hpp>
#include <radial.hpp>

//we call superclass' constructor (kernel class)
radial::radial(cloud* data_, double bandwidth_):kernel(data_){
	bandwidth = bandwidth_;
}

double radial::density(const point& p) const
{
	double density = 0;

	double n = (double)data->get_n();
	double d = (double)p.get_dim();

	double volume = this->volume();

	for(int i=0; i<n; i++){
		double t = pow( p.dist( data->get_point(i) )/bandwidth, 2 ) ;
		double profile_t = this->profile(t);

		density += profile_t/(n*pow(bandwidth, d)*volume);
	}

	return density;
}
