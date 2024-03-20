#include <iostream>
#include <cassert>
#include <cmath>	// for sqrt, fabs
#include <cfloat>	// for DBL_MAX
#include <cstdlib>	// for rand, srand
#include <ctime>	// for rand seed
#include <fstream>
#include <cstdio>	// for EOF
#include <string>
#include <algorithm>	// for count
#include <vector>

using std::rand;
using std::srand;
using std::time;

class point
{
    public:

        static int d;
        double *coords;
        int label; //partition function (indicates cluster point belongs to)

		point(){
			coords = (double *)calloc(d, sizeof(double));//allocate and initialize to 0
			label = 0;
		}

		point(point &p){
			this->coords = (double *)calloc(d, sizeof(double));
			for(int i=0; i<d; i++){
				this->coords[i] = p.coords[i];
			}
			this->label = p.label;
		}

		~point(){
			free(coords);
		}

		void print() const{
			for(int i=0; i<d; i++){
				if(i>0)std::cout<<"\t";
				std::cout << coords[i];
			}
			std::cout<<"\n";
		}

		double squared_dist(const point &q) const{
			double dist = 0;
			for(int i=0; i<d; i++){
				dist += pow(this->coords[i] - q.coords[i], 2);
			}
			return dist;
		}

		point operator-(point q){
			point aux;
			for(int i=0; i<d; i++){
				aux.coords[i] = this->coords[i] - q.coords[i];
			}
			return aux;
		}
};

int point::d;


class cloud
{
	private:

	int d;
	int n;
	int k;

	// maximum possible number of points
	int nmax;

	point *points;
	point *centers;


	public:

	cloud(int _d, int _nmax, int _k)
	{
		d = _d;
		point::d = _d;
		n = 0;
		k = _k;

		nmax = _nmax;

		points = new point[nmax];
		centers = new point[k];

		srand(time(0));
	}

	~cloud()
	{
		delete[] centers;
		delete[] points;
	}

	void add_point(const point &p, int label)
	{
		for(int m = 0; m < d; m++)
		{
			points[n].coords[m] = p.coords[m];
		}

		points[n].label = label;

		n++;
	}

	int get_d() const
	{
		return d;
	}

	int get_n() const
	{
		return n;
	}

	int get_k() const
	{
		return k;
	}

	point &get_point(int i) const
	{
		return points[i];
	}

	point &get_center(int j) const
	{
		return centers[j];
	}

	void set_center(const point &p, int j)
	{
		for(int m = 0; m < d; m++)
			centers[j].coords[m] = p.coords[m];
	}

	double intracluster_variance() const
	{
		double ret = 0;
		for(int i=0; i<n; i++){
			point p_i = get_point(i);
			point c_i = get_center(p_i.label);
			ret += p_i.squared_dist(c_i);
		}
		ret = ret/n;
		return ret;
	}

	int set_voronoi_labels()
	{
		int ret = 0;

		for(int i=0; i<n; i++){
			point p_i = get_point(i);//we want to update label of p_i (check if it has to change cluster)

			int j = 0;
			int arg_min_j = p_i.label;//initial estimate for min
			double min_dist = p_i.squared_dist(get_center(p_i.label));
			do{
				point c_i = get_center(j);
				double dist = p_i.squared_dist(c_i);
				if(dist < min_dist){
					min_dist = dist;
					arg_min_j = j;
				}
				j++;
			}while(j < k);

			if(arg_min_j != p_i.label){//MUST CHANGE CLUSTER!!!
				ret++;
				p_i.label = arg_min_j;
			}
		}

		return ret;
	}

	void set_centroid_centers()
	{
	}

	void init_random_partition()
	{
	}

	void lloyd()
	{
	}

	void init_forgy()
	{
	}

	void init_plusplus()
	{
	}
};
