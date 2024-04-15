#include<iostream>
#include"Matrix.h"

using namespace std;

//Фомин Фёдор, 11 группа
int main()
{
	srand(time(0));
	Rational a1(5, 6), b1(-4, 10);
	vector<vector<int>> x(5, vector<int>(6)), y(6, vector<int>(4));
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			x[i][j] = rand() % 10 + 1;
		}
	}
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			y[i][j] = rand() % 10 + 1;
		}
	}
	Matrix<5, 6> a(x), b(x);
	Matrix<6, 4> c(y);
	cout << a << "\n************\n" << b << "\n************\n" << c << "\n************\n";
	a += b;
	cout << a << "\n************\n";
	a -= b;
	cout << a << "\n************\n";
	a = -a;
	cout << a << "\n************\n";
	//a += c;
	Matrix<5, 4> sum = a * c;
	cout << sum << "\n************\n";
	Matrix<4, 5> sum1(5);
	sum1 = sum.transposed();
	cout << sum1 << "\n************\n";
	//sum = a * b;
	x.resize(5);
	for (int i = 0; i < 5; i++)
	{
		x[i].resize(5);
		for (int j = 0; j < 5; j++)
		{
			x[i][j] = rand() % 10 + 1;
		}
	}
	Matrix<5, 5> d, e(x), k(x);
	cout << d << "\n************\n" << e << "\n************\n";
	cout << d.trace() << "\n************\n";
	e *= e;
	cout << e << "\n************\n";
	cout << k << "\n************\n";
	cout << k.det() << "\n************\n";
	cout << k.rank() << "\n************\n";
	return 0;
}