#include "Matrix.hpp"

	// Assignment
Matrix& Matrix::Matrix::operator=(const Matrix& rhs) {

	// case trivial: same objects
	if(this == &rhs) return *this;

	// if the dimensions of the two matrices are unequal,
	// make new arrays for this matrix
	if(
		(this->rowCount() != rhs.rowCount())
		|| (this->colCount() != rhs.colCount())
	)	{

		this->destroyMatrix();

		// case other is empty
		if(!rhs.rowCount() || !rhs.colCount())
			return *this;

		this->row_count = rhs.rowCount();
		this->column_count = rhs.colCount();

		this->data = Matrix::createMatrix(this->rowCount(), this->colCount());

		for(size_t j = 0;j < this->rowCount();++j)
			for(size_t i = 0;i < this->colCount();++i)
				(*this)[j][i] = rhs[j][i];

		return *this;
	}

	// case this is empty meaning rhs is empty
	if(!this->rowCount() || !this->colCount()) return *this;

	// copy rhs.data into this->data
	for(size_t j = 0;j < this->rowCount();++j)
		for(size_t i = 0;i < this->colCount();++i)
			(*this)[j][i] = rhs[j][i];

	return *this;
}

double* Matrix::operator[](const size_t& rIndex) const {
	return this->data[rIndex];
}

double* Matrix::operator[](const size_t& rIndex) {
	return this->data[rIndex];
}

	// Binary

Matrix Matrix::operator+(const Matrix& rhs) const {
	Matrix ret = *this;
	ret += rhs;
	return ret;
}

Matrix Matrix::operator-(const Matrix& rhs) const {
	Matrix ret = *this;
	ret -= rhs;
	return ret;
}

Matrix Matrix::operator*(const Matrix& rhs) const {
	Matrix ret = *this;
	ret *= rhs;
	return ret;
}

Matrix Matrix::operator*(const double& rhs) const {
	Matrix ret = *this;
	ret *= rhs;
	return ret;
}

	// Binary Assignment

Matrix& Matrix::operator+=(const Matrix& rhs) {
	if(	this->rowCount() != rhs.rowCount()
		|| this->colCount() != rhs.colCount()
	) {
		std::cerr << "ERROR - Matrix::operator+=(const Matrix& rhs)\n";
		std::cerr << "\tthis dimensions != rhs dimensions\n";
		return *this;
	}
	for(size_t j = 0;j < this->rowCount();++j)
		for(size_t i = 0;i < this->colCount();++i)
			(*this)[j][i] += rhs[j][i];
	return *this;
}

Matrix& Matrix::operator-=(const Matrix& rhs) {
	if(	this->rowCount() != rhs.rowCount()
		|| this->colCount() != rhs.colCount()
	) {
		std::cerr << "ERROR - Matrix::operator-=(const Matrix& rhs)\n";
		std::cerr << "\tthis dimensions != rhs dimensions\n";
		return *this;
	}
	for(size_t j = 0;j < this->rowCount();++j)
		for(size_t i = 0;i < this->colCount();++i)
			(*this)[j][i] -= rhs[j][i];
	return *this;
}

Matrix& Matrix::operator*=(const Matrix& rhs) {
	if(	this->rowCount() != rhs.rowCount()
		|| this->colCount() != rhs.colCount()
	) {
		std::cerr << "ERROR - Matrix::operator*=(const Matrix& rhs)\n";
		std::cerr << "\tthis dimensions != rhs dimensions\n";
		return *this;
	}

	Matrix temp = Matrix(*this);
	*this = Matrix(this->rowCount(), rhs.colCount());

	for(size_t outCol = 0;outCol < rhs.colCount();++outCol) {
		for(size_t row = 0;row < temp.rowCount();++row) {
			double sum = 0.0;
			for(size_t inCol = 0;inCol < temp.colCount();++inCol)
				sum += temp[row][inCol] * rhs[inCol][outCol];

			(*this)[row][outCol] = sum;
		}
	}

	return *this;
}

Matrix& Matrix::operator*=(const double& rhs) {
	for(size_t j = 0;j < this->rowCount();++j)
		for(size_t i = 0;i < this->colCount();++i)
			(*this)[j][i] *= rhs;
	return *this;
}

	// Unary

Matrix Matrix::operator-() const {
	return *this * -1.0;
}

Matrix Matrix::operator~() const {
	Matrix ret = Matrix(this->colCount(), this->rowCount());

	for(size_t j = 0;j < ret.rowCount();++j)
		for(size_t i = 0;i < ret.colCount();++i)
			ret[j][i] = (*this)[i][j];

	return ret;
}

	// ostream

std::ostream& operator<<(std::ostream& os, const Matrix& other) {
	os << "[ <Matrix>\n";
	size_t lastRow = other.rowCount() - 1;
	size_t lastColumn = other.colCount() - 1;
	// print all but the last row
	for(size_t j = 0;j < lastRow;++j) {
		os << "[";
		// print all but the last column
		for(size_t i = 0;i < lastColumn;++i)
			os << "\t" << other[j][i] << ",";
		// print last column
		os << "\t" << other[j][lastColumn] << "],\n";
	}
	// print last row
	os << "[";
	// print all but the last column
	for(size_t i = 0;i < lastColumn;++i)
		os << "\t" << other[lastRow][i] << ",";
	// print last column
	os << "\t" << other[lastRow][lastColumn] << "]\n";
	return os << "] </Matrix>";
}
