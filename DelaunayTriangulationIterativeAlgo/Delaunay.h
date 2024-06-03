#pragma once
#include<iostream>
#include<vector>

using namespace std;
using D_point = pair<int, int>;
using D_triangle = pair<pair<int, int>, int>;

// ласс, реализующий “риангул€цию ƒелоне итеративным алгоритмом
class Delaunay
{
private:
	//¬ектор множества точек
	vector<D_point> Points;
	//¬ектор выпуклой оболочки множества точек текущей триангул€ции с левосторонним обходом
	vector<int> Convex_Hull;
	//ћножество векторов AiAj, i!=j, где i - номер строки, а j - номер столбца
	vector<vector<D_point>> Vector_Table;
	//ћножество треугольников триангул€ции
	vector<D_triangle> Triangles;
	//√раф, где вершины - треугольники текущей триангул€ции, а рЄбра - общие ребра смежных треугольников
	vector<vector<int>> Graph;
	//ћножество рЄбер, видимых из текущей триангул€ции
	vector<vector<int>> Link_Table;
public:
	Delaunay(vector<D_point> points) : Points(points)
	{
		Vector_Table.resize(Points.size());
		Link_Table.resize(Points.size());
		for (int i = 0; i < Points.size(); i++)
		{
			Vector_Table[i].resize(Points.size());
			Link_Table[i].resize(Points.size());
		}
	}
	void Start_Triangulation()
	{
		if (Points.size() < 3)
		{
			cerr << "Not enough points for triangulation!";
			exit(1);
		}
		Vector_Table[0][1] = make_pair(Points[1].first - Points[0].first, Points[1].second - Points[0].second);
		Vector_Table[0][2] = make_pair(Points[2].first - Points[0].first, Points[2].second - Points[0].second);
		if (Vector_Table[0][1].first * Vector_Table[0][2].second - Vector_Table[0][1].second * Vector_Table[0][2].first > 0)
		{
			Convex_Hull.push_back(0);
			Convex_Hull.push_back(1);
			Convex_Hull.push_back(2);
			Convex_Hull.push_back(0);
		}
		else
		{
			Convex_Hull.push_back(0);
			Convex_Hull.push_back(2);
			Convex_Hull.push_back(1);
			Convex_Hull.push_back(0);
		}
		Triangles.push_back(make_pair(make_pair(0, 1), 2));
		bool inside_convex_hull = 0;
		for (int i = 4; i < Points.size(); i++)
		{
			for (int j = 0; j < Triangles.size(); j++)
			{
				Check_Triangles(i, j);
			}
		}
	}
	int Check_Triangles(int i, int j)
	{
		Vector_Table[Triangles[j].first.first][i] = make_pair(Points[i].first - Points[Triangles[j].first.first].first, Points[i].second - Points[Triangles[j].first.first].first);
		vector<vector<double>> check_triangle;
		check_triangle.resize(2);
		check_triangle[0].push_back(Vector_Table[Triangles[j].first.first][Triangles[j].first.second].first);
		check_triangle[1].push_back(Vector_Table[Triangles[j].first.first][Triangles[j].first.second].second);
		check_triangle[0].push_back(Vector_Table[Triangles[j].first.first][Triangles[j].second].first);
		check_triangle[1].push_back(Vector_Table[Triangles[j].first.first][Triangles[j].second].second);
		check_triangle[0].push_back(Vector_Table[Triangles[j].first.first][i].first);
		check_triangle[1].push_back(Vector_Table[Triangles[j].first.first][i].second);
		check_triangle[0][1] /= check_triangle[0][0];
		check_triangle[0][2] /= check_triangle[0][0];
		check_triangle[0][0] = 1;
		check_triangle[1][1] -= check_triangle[0][1] * check_triangle[1][0];
		check_triangle[1][2] -= check_triangle[0][2] * check_triangle[1][0];
		check_triangle[1][0] = 0;
		check_triangle[1][2] /= check_triangle[1][1];
		check_triangle[1][1] = 1;
		check_triangle[0][2] -= check_triangle[1][2] * check_triangle[0][1];
		check_triangle[0][1] = 0;
		if (check_triangle[0][2] >= 0 && check_triangle[1][2] >= 0 && check_triangle[0][2] + check_triangle[1][2] <= 1)
		{
			return 3;
		}
		else
		{
			return 1;
		}
	}
};