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

	point &get_point(int i)
	{
		return points[i];
	}

	point &get_center(int j)
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
		return 0.0;
	}

	int set_voronoi_labels()
	{

		return 0;
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
