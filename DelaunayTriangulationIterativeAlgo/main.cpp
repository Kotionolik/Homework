#include<iostream>
#include"Delaunay.h"

using namespace std;

int main()
{
	vector<D_point> points;
	points.push_back(make_pair(10, 2));
	points.push_back(make_pair(9, 4));
	points.push_back(make_pair(-3, 6));
	points.push_back(make_pair(-3, 8));
	points.push_back(make_pair(0, -8));
	points.push_back(make_pair(0, -7));
	points.push_back(make_pair(1, -2));
	Delaunay D(points);
	D.Start_Triangulation();
	return 0;
}