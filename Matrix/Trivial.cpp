#include "../Matrix.hpp"

size_t Matrix::rowCount() const { return this->row_count; }

size_t Matrix::colCount() const { return this->col_count; }

Vector Matrix::rowVec(const size_t& index) const {
	Vector ret(this->colCount());
	for(size_t i = 0;i < this->colCount();++i)
		ret[i] = (*this)[index][i];
	return ret;
}

Vector Matrix::colVec(const size_t& index) const {
	Vector ret(this->rowCount());
	for(size_t j = 0;j < this->rowCount();++j)
		ret[j] = (*this)[j][index];
	return ret;
}

void Matrix::setRowVec(const size_t& index, const Vector& vec) {
	for(size_t i = 0;i < this->colCount();++i)
		(*this)[index][i] = vec[i];
}

void Matrix::setColVec(const size_t& index, const Vector& vec) {
	for(size_t j = 0;j < this->rowCount();++j)
		(*this)[j][index] = vec[j];
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

void Matrix::reduceFPE() {
	for(size_t j = 0;j < this->rowCount();++j)
		for(size_t i = 0;i < this->colCount();++i)
			if(Matrix::almostInt((*this)[j][i]))
				(*this)[j][i] = (double)(int)(*this)[j][i];
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
