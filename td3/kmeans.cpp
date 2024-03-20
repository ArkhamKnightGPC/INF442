#include <iostream>
#include <cassert>
#include <cmath>	// for sqrt, fabs
#include <cfloat>	// for DBL_MAX
#include <cstdlib>	// for rand, srand
#include <ctime>	// for rand seed
#include <fstream>
#include <cstdio>	// for EOF
#include <string>
#include <algorithm>	// for count, min
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

		point(const point &p){
			this->coords = (double *)calloc(d, sizeof(double));//to avoid double free
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

		point operator+(const point& q) const {
			for(int i = 0; i < d; i++) {
				this->coords[i] = this->coords[i] + q.coords[i];
			}
			return *this;
		}

		point operator-(const point& q) const {
			for(int i=0; i<d; i++){
				this->coords[i] = this->coords[i] - q.coords[i];
			}
			return *this;
		}

		point operator/(double x) const{
			for(int i=0; i<d; i++){
				this->coords[i] = this->coords[i]/x;
			}
			return *this;
		}

		point& operator=(const point& p) {
			if (this != &p) {

				free(coords);//to avoid leak we free before copying

				coords = (double *)calloc(d, sizeof(double));
				for(int i = 0; i < d; i++) {
					coords[i] = p.coords[i];
				}
			}
			return *this;
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

	void update_label(int i, int label){
		points[i].label = label;
	}

	void update_center(int i, point center){
		centers[i] = center;
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
				update_label(i, arg_min_j);
			}
		}

		return ret;
	}

	void set_centroid_centers()
	{
		int* count = (int *)calloc(k, sizeof(int));
		point* temp_centers = (point *)calloc(k, sizeof(point));//temporary storage to calculate new centers

		for(int i=0; i<k; i++){
			temp_centers[i] = get_center(i);
		}

		for(int i=0; i<n; i++){
			point p_i = get_point(i);

			int c_i = p_i.label;
			if(count[c_i] == 0){
				temp_centers[c_i] = p_i;//reset center
			}else{
				temp_centers[c_i] = temp_centers[c_i] + p_i;
			}
			count[c_i]++;
		}

		for(int i=0; i<k; i++){

			if(count[i] > 0)
				temp_centers[i] = temp_centers[i]/count[i];//compute mean
			
			update_center(i, temp_centers[i]);//update actual center
		}

		free(count);
		free(temp_centers);
	}

	void init_random_partition()
	{
		for(int i=0; i<n; i++){
			update_label(i, rand()%k);
		}
	}

	void lloyd()
	{
		init_random_partition();//start with random labels

		do{//until centroids converge
			set_centroid_centers();//update centers
		}while(set_voronoi_labels() > 0);//update labels
	}

	void init_forgy()
	{
		int *chk = (int *)calloc(n, sizeof(int));
		for(int i=0; i<n; i++)
			chk[i] = i;

		for(int i=0; i<k; i++){
			int choice = std::rand()%(n-i);
			update_center(i, get_point(chk[choice]));
			std::swap(chk[n-i-1], chk[choice]);
		}

		free(chk);
	}

	void init_plusplus()
	{
		update_center(0, get_point(rand()%n));//c0 chosen uniformly at random

		double *dists = (double *)calloc(n, sizeof(double));

		for(int i=1; i<k; i++){//furthest point sampling
			double sum_dist = 0;

			for(int j=0; j<n; j++){

				point p_j = get_point(j);

				double min_dist = MAXFLOAT;

				if(i == 1){
					dists[j] = p_j.squared_dist(get_center(0));
				}else{
					dists[j] = std::min(dists[j], p_j.squared_dist(get_center(i-1)));
				}
				sum_dist += dists[j];
			}

			double rand = (double)std::rand() / RAND_MAX;
			double aux = 0;
			bool flag = true;
			for(int j=0; j<n && flag; j++){
				aux += dists[j]/sum_dist;
				if(aux >= rand && flag){
					update_center(i, get_point(j));
					flag = false;
				}
			}
		}

		free(dists);
	}
};
