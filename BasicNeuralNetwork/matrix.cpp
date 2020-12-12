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

Matrix::Matrix(const Matrix& m) {
	m_rows = m.m_rows;
	m_cols = m.m_cols;
	m_data = m.m_data;
}

void Matrix::FillData(double value) {
	m_data.assign(m_rows, std::vector<double>(m_cols, 0));
	for (std::vector<double> &row : m_data) {
		for (double &val : row) {
			val = value;
		}
	}
}

void Matrix::FillData(int mean, int deviation) {
	std::random_device ran;
	std::default_random_engine generator(ran());
	std::normal_distribution<double> distribution(mean, deviation);

	m_data.assign(m_rows, std::vector<double>(m_cols, 0));

	for (std::vector<double> &row : m_data) {
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

std::vector<std::vector<double>> Matrix::GetData() {
	return m_data;
}

std::pair<int, int> Matrix::GetShape()
{
	std::pair<int, int> size;
	size = std::make_pair(m_rows, m_cols);
	return size;
}

std::string Matrix::ToString() {
	bool negativeIncluded = false;

	for (std::vector<double> row : m_data) {
		for (double value : row) {
			if (value < 0) negativeIncluded = true;
		}
	}

	std::string str = "";
	for (unsigned int i = 0; i < m_data.size(); i++) {
		str += (i == 0 ? "[" : " ");
		for (unsigned int j = 0; j < m_data[i].size(); j++) {
			str += (j == 0 ? "[" : "") + (std::string)(m_data[i][j] >= 0 && negativeIncluded ? " " : "") + std::to_string(m_data[i][j]) + (j == m_data[i].size() - 1 ? "]" : " ");
		}
		str += (i == m_data.size() - 1 ? "]" : "\n");
	}
	return str;
}

std::vector<std::vector<double>>& Matrix::ToVector() {
	return m_data;
}

double& Matrix::At(int row, int col) {
	return m_data[row][col];
}

std::vector<double> Matrix::RowAt(int rowIndex)
{
	return m_data[rowIndex];
}

std::vector<double> Matrix::ColAt(int colIndex)
{
	std::vector<double> col;
	for (std::vector<double> row : m_data) {
		col.push_back(row.at(colIndex));
	}
	return col;
}

Matrix Matrix::operator=(const Matrix& m) {
	if (this != &m) {
		m_rows = m.m_rows;
		m_cols = m.m_cols;
		m_data = m.m_data;
	}
	return *this;
}

Matrix Matrix::operator+(const Matrix& m) {
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

Matrix Matrix::operator-(const Matrix& m) {
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

Matrix Matrix::operator*(const double& scalar) {
	Matrix m = *this;
	for (std::vector<double> &row : m.m_data) {
		for (double &value : row) {
			value *= scalar;
		}
	}
	return m;
}

Matrix Matrix::operator/(const double& scalar) {
	Matrix m = *this;
	for (std::vector<double> &row : m.m_data) {
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
	for (std::vector<double> &row : m_data) {
		for (double &value : row) {
			value *= scalar;
		}
	}
	return *this;
}

Matrix Matrix::operator/=(const double& scalar) {
	for (std::vector<double> &row : m_data) {
		for (double &value : row) {
			value /= scalar;
		}
	}
	return *this;
}

std::vector<double>& Matrix::operator[](const int& row) {
	return m_data.at(row);
}