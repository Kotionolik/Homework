#pragma once
#include<iostream>
#include<algorithm>
#include<vector>
#include<string>

using namespace std;

class Rational;
template<size_t M, size_t N, typename Field = Rational>
class Matrix;

int gcd(int a, int b)
{
	return b ? gcd(b, a % b) : a;
}

class Rational {
protected:
	int numerator, denominator;
public:
	Rational() : numerator(0), denominator(1) {}
	Rational(int x) : numerator(x), denominator(1) {}
	Rational(int x, int y) : numerator(x), denominator(y) { ToComfraction(); }
	void CheckDenZero()
	{
		if (denominator == 0)
		{
			throw exception();
		}
	}
	void ToComfraction()
	{
		CheckDenZero();
		if (denominator < 0)
		{
			denominator *= -1;
			numerator *= -1;
		}
		int g = gcd(abs(numerator), denominator);
		numerator /= g;
		denominator /= g;
	}
	Rational& operator=(const Rational& x)
	{
		if (this != &x)
		{
			numerator = x.numerator;
			denominator = x.denominator;
		}
		return *this;
	}
	Rational& operator=(const int& x)
	{
		numerator = x;
		denominator = 1;
		return *this;
	}
	int& operator=(const Rational& x) const
	{
		int a = 0;
		a = numerator / denominator;
		return a;
	}
	const Rational operator-() const
	{
		Rational x(-numerator, denominator);
		return x;
	}
	Rational& operator+=(const Rational& x)
	{
		numerator *= x.denominator;
		numerator += x.numerator * denominator;
		denominator *= x.denominator;
		ToComfraction();
		return *this;
	}
	Rational& operator+=(const int& x)
	{
		numerator += x * denominator;
		ToComfraction();
		return *this;
	}
	const Rational operator+(const Rational& x) const
	{
		Rational y((numerator * x.denominator) + (x.numerator * denominator), (denominator * x.denominator));
		return y;
	}
	const Rational operator+(const int& x) const
	{
		Rational y(numerator + (x * denominator), denominator);
		return y;
	}
	Rational& operator-=(const Rational& x)
	{
		operator+=(-x);
		return *this;
	}
	const Rational operator-(const Rational& x) const
	{
		return operator+(-x);
	}
	Rational& operator-=(const int& x)
	{
		operator+=(-x);
		return *this;
	}
	const Rational operator-(const int& x) const
	{
		return operator+(-x);
	}
	Rational& operator*=(const Rational& x)
	{
		numerator *= x.numerator;
		denominator *= x.denominator;
		ToComfraction();
		return *this;
	}
	Rational& operator*=(const int& x)
	{
		numerator *= x;
		ToComfraction();
		return *this;
	}
	const Rational operator*(const Rational& x) const
	{
		Rational y(numerator * x.numerator, denominator * x.denominator);
		return y;
	}
	const Rational operator*(const int& x) const
	{
		Rational y(numerator * x, denominator);
		return y;
	}
	Rational& operator/=(const Rational& x)
	{
		numerator *= x.denominator;
		denominator *= x.numerator;
		ToComfraction();
		return *this;
	}
	Rational& operator/=(const int& x)
	{
		denominator *= x;
		ToComfraction();
		return *this;
	}
	const Rational operator/(const Rational& x) const
	{
		Rational y(numerator * x.denominator, denominator * x.numerator);
		return y;
	}
	const Rational operator/(const int& x) const
	{
		Rational y(numerator, denominator * x);
		return y;
	}
	bool operator==(const Rational& x) const
	{
		if (denominator == x.denominator && numerator == x.numerator)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool operator!=(const Rational& x) const
	{
		return !(operator==(x));
	}
	bool operator<(const Rational & x) const
	{
		if (denominator > x.denominator)
		{
			return true;
		}
		else if (denominator == x.denominator)
		{
			if (numerator < x.numerator)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	bool operator>(const Rational & x) const
	{
		return !(operator<(x));
	}
	bool operator<=(const Rational& x) const
	{
		return (operator<(x) || operator==(x));
	}
	bool operator>=(const Rational& x) const
	{
		return (operator>(x) || operator==(x));
	}
	friend ostream& operator<<(ostream& out, const Rational& data)
	{
		out << data.numerator << '/' << data.denominator;
		return out;
	}
	friend istream& operator>>(istream& in, Rational& data)
	{
		string str;
		in >> str;
		if (str.find('/') != -1)
		{
			data.numerator = stoi(str.substr(0, str.find('/')));
			str.erase(0, str.find('/') + 1);
			data.denominator = stoi(str);
		}
		else
		{
			data.numerator = stoi(str);
			data.denominator = 1;
		}
		data.ToComfraction();
		return in;
	}
};
template<size_t M, size_t N, typename Field>
class Matrix
{
protected:
	vector<vector<Field>> mat;
public:
	int size()
	{
		return mat.size();
	}
	void resize(int x)
	{
		mat.resize(x);
	}
	vector<Field>& operator[](int index)
	{
		return mat[index];
	}
	const vector<Field> operator[](int index) const
	{
		return mat[index];
	}
	Matrix() = delete;
	Matrix(const Field& x) : mat(M, vector<Field>(N, x)) {}
	Matrix(const Matrix& x)
	{
		if (M != x.mat.size())
		{
			throw exception();
		}
		else
		{
			mat.resize(M);
			if (N != x.mat[0].size())
			{
				throw exception();
			}
			for (int i = 0; i < M; i++)
			{
				mat[i].resize(N);
				for (int j = 0; j < N; j++)
				{
					mat[i][j] = x[i][j];
				}
			}
		}
	}
	bool operator==(const Matrix& x)
	{
		if (mat.size() != x.mat.size() || mat[0].size() != x.mat[0].size())
		{
			return false;
		}
		else
		{
			for (int i = 0; i < M; i++)
			{
				for (int j = 0; j < N; j++)
				{
					if (mat[i][j] != x[i][j])
					{
						return false;
					}
				}
			}
			return true;
		}
	}
	bool operator!=(const Matrix& x)
	{
		return !(operator==(x));
	}
	template<typename T>
	Matrix(const vector<vector<T>>& v)
	{
		if (M != v.size())
		{
			throw exception();
		}
		else
		{
			mat.resize(M);
			for (int i = 0; i < M; i++)
			{
				if (N != v[i].size())
				{
					throw exception();
				}
				else
				{
					mat[i].resize(N);
					for (int j = 0; j < N; j++)
					{
						mat[i][j] = v[i][j];
					}
				}
			}
		}
	}
	const Matrix operator-() const
	{
		Matrix x(*this);
		for (int i = 0; i < M; i++)
		{
			for (int j = 0; j < N; j++)
			{
				x[i][j] = -mat[i][j];
			}
		}
		return x;
	}
	Matrix& operator=(const Matrix<M, N>& x)
	{
		if (this != &x)
		{
			for (int i = 0; i < M; i++)
			{
				for (int j = 0; j < N; j++)
				{
					mat[i][j] = x[i][j];
				}
			}
		}
		return *this;
	}
	Matrix& operator+=(const Matrix<M, N>& x)
	{
		for (int i = 0; i < M; i++)
		{
				for (int j = 0; j < N; j++)
				{
					mat[i][j] += x[i][j];
				}
		}
		return *this;
	}
	Matrix& operator-=(const Matrix<M, N>& x)
	{
		operator+=(-x);
		return *this;
	}
	template<typename T>
	Matrix& operator*=(const T& x)
	{
		Matrix<M, N> y(0);
		for (int i = 0; i < M; i++)
		{
			for (int j = 0; j < N; j++)
			{
				y[i][j] = *this[i][j];
				y[i][j] *= x;
			}
		}
		*this = y;
		return *this;
	}
	template<typename T>
	const Matrix operator*(const T& x) const
	{
		Matrix<M, N> y(0);
		for (int i = 0; i < M; i++)
		{
			for (int j = 0; j < N; j++)
			{
				y[i][j] = *this[i][j];
				y[i][j] *= x;
			}
		}
		return y;
	}
	template<size_t K>
	const Matrix<M, K> operator*(const Matrix<N, K>& x) const
	{
		Matrix<M, K> y(0);
		for (int i = 0; i < M; i++)
		{
			for (int j = 0; j < K; j++)
			{
				y[i][j] = 0;
				for (int k = 0; k < N; k++)
				{
					y[i][j] += mat[i][k] * x[k][j];
				}
			}
		}
		return y;
	}
	Field det() const = delete;
	const Matrix<N, M> transposed() const
	{
		Matrix<N, M> y(0);
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
			{
				y[i][j] = mat[j][i];
			}
		}
		return y;
	}
	int rank() const
	{
		int rk = 0, currk = 0;
		Field tmp;
		Matrix<M, M> dtr;
		dtr = *this;
		for (int k = 0; k < M - 1; k++)
		{
			for (int i = k + 1; i < M; i++)
			{
				tmp = -dtr[i][k] / dtr[k][k];
				for (int j = 0; j < M; j++)
				{
					dtr[i][j] += (dtr[k][j] * tmp);
				}
			}
		}
		for (int i = 0; i < M; i++)
		{
			if (dtr[i][i] != 0)
			{
				currk++;
			}
			else
			{
				rk = max(rk, currk);
				currk = 0;
			}
		}
		rk = max(rk, currk);
		return rk;
	}
	Field trace() = delete;
	void invert() = delete;
	const Matrix inverted() const = delete;
	vector<Field> getRow(size_t m) const
	{
		vector<Field> ans(M);
		for (int i = 0; i < M; i++)
		{
			ans[i] = mat[m][i];
		}
		return ans;
	}
	vector<Field> getColumn(size_t n) const
	{
		vector<Field> ans(N);
		for (int i = 0; i < N; i++)
		{
			ans[i] = mat[i][n];
		}
		return ans;
	}
	friend ostream& operator<<(ostream& out, const Matrix& data)
	{
		for (int i = 0; i < M; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (j < N - 1)
				{
					out << data[i][j] << ' ';
				}
				else
				{
					out << data[i][j];
				}
			}
			if (i < M - 1)
			{
				out << '\n';
			}
		}
		return out;
	}
};

template<size_t M, typename Field>
class Matrix<M, M, Field>
{
protected:
	vector<vector<Field>> mat;
public:
	int size()
	{
		return mat.size();
	}
	void resize(int x)
	{
		mat.resize(x);
	}
	vector<Field>& operator[](int index)
	{
		return mat[index];
	}
	const vector<Field> operator[](int index) const
	{
		return mat[index];
	}
	Matrix()
	{
		mat.resize(M);
		for (int i = 0; i < M; i++)
		{
			mat[i].resize(M);
			mat[i][i] = 1;
		}
	}
	Matrix(const Field& x) : mat(M, vector<Field>(M, x)) {}
	Matrix(const Matrix<M, M>& x)
	{
		if (M != x.mat.size())
		{
			throw exception();
		}
		else
		{
			mat.resize(M);
			if (M != x.mat[0].size())
			{
				throw exception();
			}
			for (int i = 0; i < M; i++)
			{
				mat[i].resize(M);
				for (int j = 0; j < M; j++)
				{
					mat[i][j] = x[i][j];
				}
			}
		}
	}
	bool operator==(const Matrix& x)
	{
		if (mat.size() != x.mat.size() || mat[0].size() != x.mat[0].size())
		{
			return false;
		}
		else
		{
			for (int i = 0; i < M; i++)
			{
				for (int j = 0; j < M; j++)
				{
					if (mat[i][j] != x[i][j])
					{
						return false;
					}
				}
			}
			return true;
		}
	}
	bool operator!=(const Matrix& x)
	{
		return !(operator==(x));
	}
	template<typename T>
	Matrix(const vector<vector<T>>& v)
	{
		if (M != v.size())
		{
			throw exception();
		}
		else
		{
			mat.resize(M);
			for (int i = 0; i < M; i++)
			{
				if (M != v[i].size())
				{
					throw exception();
				}
				else
				{
					mat[i].resize(M);
					for (int j = 0; j < M; j++)
					{
						mat[i][j] = v[i][j];
					}
				}
			}
		}
	}
	const Matrix operator-() const
	{
		Matrix x(*this);
		for (int i = 0; i < M; i++)
		{
			for (int j = 0; j < M; j++)
			{
				x[i][j] = -mat[i][j];
			}
		}
		return x;
	}
	Matrix& operator=(const Matrix<M, M>& x)
	{
		if (this != &x)
		{
			for (int i = 0; i < M; i++)
			{
				for (int j = 0; j < M; j++)
				{
					mat[i][j] = x[i][j];
				}
			}
		}
		return *this;
	}
	Matrix& operator+=(const Matrix<M, M>& x)
	{
		for (int i = 0; i < M; i++)
		{
			for (int j = 0; j < M; j++)
			{
				mat[i][j] += x[i][j];
			}
		}
		return *this;
	}
	Matrix& operator-=(const Matrix<M, M>& x)
	{
		operator+=(-x);
		return *this;
	}
	template<size_t K>
	const Matrix<M, K> operator*(const Matrix<M, K>& x) const
	{
		Matrix<M, K> y(0);
		for (int i = 0; i < M; i++)
		{
			for (int j = 0; j < K; j++)
			{
				for (int k = 0; k < M; k++)
				{
					y[i][j] += mat[i][k] * x[k][j];
				}
			}
		}
		return y;
	}
	template<typename T>
	Matrix& operator*=(const T& x)
	{
		Matrix<M, M> y(0);
		for (int i = 0; i < M; i++)
		{
			for (int j = 0; j < M; j++)
			{
					y[i][j] = *this[i][j];
					y[i][j] *= x;
			}
		}
		*this = y;
		return *this;
	}
	template<typename T>
	const Matrix operator*(const T& x) const
	{
		Matrix<M, M> y(0);
		for (int i = 0; i < M; i++)
		{
			for (int j = 0; j < M; j++)
			{
					y[i][j] = *this[i][j];
					y[i][j] *= x;
			}
		}
		return y;
	}
	Matrix& operator*=(const Matrix<M, M>& x)
	{
		Matrix<M, M> y(0);
		for (int i = 0; i < M; i++)
		{
			for (int j = 0; j < M; j++)
			{
				for (int k = 0; k < M; k++)
				{
					y[i][j] += mat[i][k] * x[k][j];
				}
			}
		}
		*this = y;
		return *this;
	}
	Field det() const
	{
		Field determinant = 1, tmp;
		Matrix<M, M> dtr;
		dtr = *this;
		for (int k = 0; k < M - 1; k++)
		{
			for (int i = k + 1; i < M; i++)
			{
				tmp = -dtr[i][k] / dtr[k][k];
				for (int j = 0; j < M; j++)
				{
					dtr[i][j] += (dtr[k][j] * tmp);
				}
			}
		}
		for (int i = 0; i < M; i++)
		{
			determinant *= dtr[i][i];
		}
		return determinant;
	}
	const Matrix<M, M> transposed() const
	{
		Matrix<M, M> y(0);
		for (int i = 0; i < M; i++)
		{
			for (int j = 0; j < M; j++)
			{
				y[i][j] = mat[j][i];
			}
		}
		return y;
	}
	int rank() const
	{
		int rk = 0, currk = 0;
		Field tmp;
		Matrix<M, M> dtr;
		dtr = *this;
		for (int k = 0; k < M - 1; k++)
		{
			for (int i = k + 1; i < M; i++)
			{
				tmp = -dtr[i][k] / dtr[k][k];
				for (int j = 0; j < M; j++)
				{
					dtr[i][j] += (dtr[k][j] * tmp);
				}
			}
		}
		for (int i = 0; i < M; i++)
		{
			if (dtr[i][i] != 0)
			{
				currk++;
			}
			else
			{
				rk = max(rk, currk);
				currk = 0;
			}
		}
		rk = max(rk, currk);
		return rk;
	}
	Field trace() const
	{
		Field ans;
		for (int i = 0; i < M; i++)
		{
			ans += mat[i][i];
		}
		return ans;
	}
	void invert()
	{
		if (det() == 0)
		{
			throw exception();
		}
		Matrix<M, M> y;
		for (int i = 0; i < M; i++)
		{
			int row = i;
			Field mx = mat[i][i];
			for (int k = i + 1; k < M; k++)
			{
				if (mat[k][i] * -1 > mx)
				{
					row = k;
					mx = mat[k][i] * -1;
				}
			}
			if (row != i)
			{
				swap(mat[row], mat[i]);
				swap(y[row], y[i]);
			}
			for (int k = i + 1; k < M; k++)
			{
				Field e = mat[k][i] / mat[i][i];
				for (int j = 0; j < M; j++)
				{
					mat[k][j] -= e * mat[i][j];
					y[k][j] -= e * y[i][j];
				}
			}
		}
		for (int i = M - 1; i >= 0; i--)
		{
			for (int j = i - 1; j >= 0; j--)
			{
				Field e = mat[j][i] / mat[i][i];
				for (int k = 0; k < M; k++)
				{
					mat[j][k] -= e * mat[i][k];
					y[j][k] -= e * y[i][k];
				}
			}
			for (int j = 0; j < M; j++)
			{
				y[i][j] /= mat[i][i];
			}
		}
		*this = y;
	}
	const Matrix inverted() const
	{
		if (det() == 0)
		{
			throw exception();
		}
		Matrix<M, M> y, z;
		z = *this;
		for (int i = 0; i < M; i++)
		{
			int row = i;
			Field mx = z[i][i];
			for (int k = i + 1; k < M; k++)
			{
				if (z[k][i] * -1 > mx)
				{
					row = k;
					mx = z[k][i] * -1;
				}
			}
			if (row != i)
			{
				swap(z[row], z[i]);
				swap(y[row], y[i]);
			}
			for (int k = i + 1; k < M; k++)
			{
				Field e = z[k][i] / z[i][i];
				for (int j = 0; j < M; j++)
				{
					z[k][j] -= e * z[i][j];
					y[k][j] -= e * y[i][j];
				}
			}
		}
		for (int i = M - 1; i >= 0; i--)
		{
			for (int j = i - 1; j >= 0; j--)
			{
				Field e = z[j][i] / z[i][i];
				for (int k = 0; k < M; k++)
				{
					z[j][k] -= e * z[i][k];
					y[j][k] -= e * y[i][k];
				}
			}
			for (int j = 0; j < M; j++)
			{
				y[i][j] /= z[i][i];
			}
		}
		return y;
	}
	vector<Field> getRow(size_t m) const
	{
		vector<Field> ans(M);
		for (int i = 0; i < M; i++)
		{
			ans[i] = mat[m][i];
		}
		return ans;
	}
	vector<Field> getColumn(size_t n) const
	{
		vector<Field> ans(M);
		for (int i = 0; i < M; i++)
		{
			ans[i] = mat[i][n];
		}
		return ans;
	}
	friend ostream& operator<<(ostream& out, const Matrix& data)
	{
		for (int i = 0; i < M; i++)
		{
			for (int j = 0; j < M; j++)
			{
				if (j < M - 1)
				{
					out << data[i][j] << ' ';
				}
				else
				{
					out << data[i][j];
				}
			}
			if (i < M - 1)
			{
				out << '\n';
			}
		}
		return out;
	}
};

template<size_t M, typename Field = Rational>
using SquareMatrix = Matrix<M, M>;