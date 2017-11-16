#include "Matrix.hpp"

size_t Matrix::rowCount() const { return this->row_count; }

size_t Matrix::colCount() const { return this->col_count; }

double* Matrix::row(const size_t& index) const {
	double* ret = new double[this->colCount()];
	for(size_t i = 0;i < this->colCount();++i)
		ret[i] = (*this)[index][i];
	return ret;
}

double* Matrix::col(const size_t& index) const {
	double* ret = new double[this->rowCount()];
	for(size_t i = 0;i < this->rowCount();++i)
		ret[i] = (*this)[i][index];
	return ret;
}

double Matrix::at(const size_t& rIndex, const size_t& cIndex) const {
	return (*this)[rIndex][cIndex];
}

void Matrix::setAt(
	const size_t& rIndex,
	const size_t& cIndex,
	const double& newNum
) {
	(*this)[rIndex][cIndex] = newNum;
}
