#include "Matrix.hpp"

size_t Matrix::rowCount() const { return this->row_count; }

size_t Matrix::colCount() const { return this->col_count; }

double* Matrix::row(double* mem, const size_t& index) const {
	for(size_t i = 0;i < this->colCount();++i)
		mem[i] = (*this)[index][i];
	return mem;
}

double* Matrix::col(double* mem, const size_t& index) const {
	for(size_t j = 0;j < this->rowCount();++j)
		mem[j] = (*this)[j][index];
	return mem;
}

bool Matrix::rowZero(const size_t& index) const {
	for(size_t i = 0;i < this->colCount();++i)
		if((*this)[index][i] != 0.0)
			return false;
	return true;
}

bool Matrix::colZero(const size_t& index) const {
	for(size_t j = 0;j < this->colCount();++j)
		if((*this)[j][index] != 0.0)
			return false;
	return true;
}

double Matrix::leadCoef(const size_t& index) const {
	for(size_t col = 0;col < this->colCount();++col)
		if((*this)[index][col] != 0.0)
			return (*this)[index][col];
	return 0.0;
}

size_t Matrix::leadIndex(const size_t& index) const {
	size_t col;
	for(col = 0;col < this->colCount();++col)
		if((*this)[index][col] != 0.0)
			return col;
	return col;
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
