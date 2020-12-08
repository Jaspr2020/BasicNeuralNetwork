#ifndef MATRIX_CPP
#define MATRIX_CPP

#include <iostream>
#include <vector>
#include <string>
#include <random>
using namespace std;

class Matrix {
public:
	Matrix();
	Matrix(int rows, int cols);
	Matrix(int rows, int cols, double value);
	Matrix(int rows, int cols, int mean, int deviation);
	void FillData(double value);
	void FillData(int mean, int deviation);
	int GetRows();
	int GetCols();
	vector<vector<double>> GetData();
	pair<int, int> GetShape();
	string ToString();
	vector<vector<double>>& ToVector();
	double& At(int row, int col);
	vector<double> RowAt(int rowIndex);
	vector<double> ColAt(int colIndex);
	Matrix operator+(const Matrix& m);
	Matrix operator-(const Matrix& m);
	Matrix operator*(const Matrix& m);
	Matrix operator*(const double& scalar);
	Matrix operator/(const double& scalar);
	Matrix operator+=(const Matrix& m);
	Matrix operator-=(const Matrix& m);
	Matrix operator*=(const double& scalar);
	Matrix operator/=(const double& scalar);
	vector<double>& operator[](const int& row);
private:
	int m_rows;
	int m_cols;
	vector<vector<double>> m_data;
};

#endif