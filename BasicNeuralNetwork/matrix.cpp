#include "matrix.h"

Matrix::Matrix() {
	m_rows = 2;
	m_cols = 2;
	FillData(0);
}

Matrix::Matrix(int rows, int cols) {
	m_rows = rows;
	m_cols = cols;
	FillData(0);
}

Matrix::Matrix(int rows, int cols, double value) {
	m_rows = rows;
	m_cols = cols;
	FillData(value);
}

Matrix::Matrix(int rows, int cols, int mean, int deviation) {
	m_rows = rows;
	m_cols = cols;
	FillData(mean, deviation);
}

void Matrix::FillData(double value) {
	m_data.assign(m_rows, vector<double>(m_cols, 0));
	for (vector<double> &row : m_data) {
		for (double &val : row) {
			val = value;
		}
	}
}

void Matrix::FillData(int mean, int deviation) {
	random_device ran;
	default_random_engine generator(ran());
	normal_distribution<double> distribution(mean, deviation);

	m_data.assign(m_rows, vector<double>(m_cols, 0));

	for (vector<double> &row : m_data) {
		for (double &value : row) {
			value = distribution(generator);
		}
	}
}

int Matrix::GetRows() {
	return m_rows;
}

int Matrix::GetCols() {
	return m_cols;
}

vector<vector<double>> Matrix::GetData() {
	return m_data;
}

pair<int, int> Matrix::GetShape()
{
	pair<int, int> size;
	size = make_pair(m_rows, m_cols);
	return size;
}

string Matrix::ToString() {
	bool negativeIncluded = false;

	for (vector<double> row : m_data) {
		for (double value : row) {
			if (value < 0) negativeIncluded = true;
		}
	}

	string str = "";
	for (unsigned int i = 0; i < m_data.size(); i++) {
		str += (i == 0 ? "[" : " ");
		for (unsigned int j = 0; j < m_data[i].size(); j++) {
			str += (j == 0 ? "[" : "") + (string)(m_data[i][j] >= 0 && negativeIncluded ? " " : "") + to_string(m_data[i][j]) + (j == m_data[i].size() - 1 ? "]" : " ");
		}
		str += (i == m_data.size() - 1 ? "]" : "\n");
	}
	return str;
}

vector<vector<double>>& Matrix::ToVector() {
	return m_data;
}

double& Matrix::At(int row, int col) {
	return m_data[row][col];
}

vector<double> Matrix::RowAt(int rowIndex)
{
	return m_data[rowIndex];
}

vector<double> Matrix::ColAt(int colIndex)
{
	vector<double> col;
	for (vector<double> row : m_data) {
		col.push_back(row.at(colIndex));
	}
	return col;
}

Matrix Matrix::operator+(const Matrix& m)
{
	if (m_rows == m.m_rows && m_cols == m.m_cols) {
		Matrix matrix(m_rows, m_cols);
		for (int i = 0; i < m_rows; i++) {
			for (int j = 0; j < m_cols; j++) {
				matrix[i][j] = m_data[i][j] + m.m_data[i][j];
			}
		}
		return matrix;
	}
	return *this;
}

Matrix Matrix::operator-(const Matrix& m)
{
	if (m_rows == m.m_rows && m_cols == m.m_cols) {
		Matrix matrix(m_rows, m_cols);
		for (int i = 0; i < m_rows; i++) {
			for (int j = 0; j < m_cols; j++) {
				matrix[i][j] = m_data[i][j] - m.m_data[i][j];
			}
		}
		return matrix;
	}
	return *this;
}

Matrix Matrix::operator*(const Matrix& m) {
	if (m_cols == m.m_rows) {
		Matrix matrix(m_rows, m.m_cols);
		for (int row = 0; row < matrix.m_rows; row++) {
			for (int col = 0; col < matrix.m_cols; col++) {
				for (int inner = 0; inner < m.m_rows; inner++) {
					matrix[row][col] += m_data[row][inner] * m.m_data[inner][col];
				}
			}
		}
		return matrix;
	}
	return *this;
}

Matrix Matrix::operator*(const double& scalar)
{
	Matrix m = *this;
	for (vector<double> &row : m.m_data) {
		for (double &value : row) {
			value *= scalar;
		}
	}
	return m;
}

Matrix Matrix::operator/(const double& scalar)
{
	Matrix m = *this;
	for (vector<double> &row : m.m_data) {
		for (double &value : row) {
			value /= scalar;
		}
	}
	return m;
}

Matrix Matrix::operator+=(const Matrix& m) {
	if (m_rows == m.m_rows && m_cols == m.m_cols) {
		for (int i = 0; i < m_rows; i++) {
			for (int j = 0; j < m_cols; j++) {
				m_data[i][j] += m.m_data[i][j];
			}
		}
	}
	return *this;
}

Matrix Matrix::operator-=(const Matrix& m) {
	if (m_rows == m.m_rows && m_cols == m.m_cols) {
		for (int i = 0; i < m_rows; i++) {
			for (int j = 0; j < m_cols; j++) {
				m_data[i][j] -= m.m_data[i][j];
			}
		}
	}
	return *this;
}

Matrix Matrix::operator*=(const double& scalar) {
	for (vector<double> &row : m_data) {
		for (double &value : row) {
			value *= scalar;
		}
	}
	return *this;
}

Matrix Matrix::operator/=(const double& scalar) {
	for (vector<double> &row : m_data) {
		for (double &value : row) {
			value /= scalar;
		}
	}
	return *this;
}

vector<double>& Matrix::operator[](const int& row) {
	return m_data.at(row);
}