#ifndef MATRIX_CPP
#define MATRIX_CPP

#include <iostream>
#include <vector>
#include <string>
#include <random>

class Matrix {
public:
	Matrix();
	Matrix(int rows, int cols);
	Matrix(int rows, int cols, double value);
	Matrix(int rows, int cols, int mean, int deviation);
	Matrix(const Matrix& m);
	void FillData(double value);
	void FillData(int mean, int deviation);
	int GetRows();
	int GetCols();
	std::vector<std::vector<double>> GetData();
	std::pair<int, int> GetShape();
	std::string ToString();
	std::vector<std::vector<double>>& ToVector();
	double& At(int row, int col);
	std::vector<double> RowAt(int rowIndex);
	std::vector<double> ColAt(int colIndex);
	Matrix operator=(const Matrix& m);
	Matrix operator+(const Matrix& m);
	Matrix operator-(const Matrix& m);
	Matrix operator*(const Matrix& m);
	Matrix operator*(const double& scalar);
	Matrix operator/(const double& scalar);
	Matrix operator+=(const Matrix& m);
	Matrix operator-=(const Matrix& m);
	Matrix operator*=(const double& scalar);
	Matrix operator/=(const double& scalar);
	std::vector<double>& operator[](const int& row);
private:
	int m_rows;
	int m_cols;
	std::vector<std::vector<double>> m_data;
};

#endif