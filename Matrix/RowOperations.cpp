#include "Matrix.hpp"

void Matrix::RO_swp(const size_t& dest, const size_t& other) {
	double temp;
	for(size_t col = 0;col < this->colCount();++col) {
		temp = (*this)[dest][col];
		(*this)[dest][col] = (*this)[other][col];
		(*this)[other][col] = temp;
	}
}

void Matrix::RO_add(const size_t& dest, const size_t& other) {
	for(size_t col = 0;col < this->colCount();++col)
		(*this)[dest][col] += (*this)[other][col];
}

void Matrix::RO_addS(
	const size_t& dest, const size_t& other, const double& scale
) {
	for(size_t col = 0;col < this->colCount();++col)
		(*this)[dest][col] += (*this)[other][col] * scale;
}

void Matrix::RO_sub(const size_t& dest, const size_t& other) {
	if(dest == other) {
		std::cerr << "ERROR - Matrix::RO_sub(...)\n";
		std::cerr << "\tdest == other\n";
		return;
	}
	for(size_t col = 0;col < this->colCount();++col)
		(*this)[dest][col] -= (*this)[other][col];
}

void Matrix::RO_subS(
	const size_t& dest, const size_t& other, const double& scale
) {
	for(size_t col = 0;col < this->colCount();++col)
		(*this)[dest][col] -= (*this)[other][col] * scale;
}


void Matrix::RO_mul(const size_t& dest, const double& scale) {
	if(scale == 0.0) {
		std::cerr << "ERROR - Matrix::RO_mul(...)\n";
		std::cerr << "\tscale == 0\n";
		return;
	}
	for(size_t col = 0;col < this->colCount();++col)
		(*this)[dest][col] *= scale;
}

void Matrix::RO_div(const size_t& dest, const double& scale) {
	if(scale == 0.0) {
		std::cerr << "ERROR - Matrix::RO_div(...)\n";
		std::cerr << "\tscale == 0\n";
		return;
	}
	for(size_t col = 0;col < this->colCount();++col)
		(*this)[dest][col] /= scale;
}

void Matrix::pivot(const size_t& rIndex) {
	size_t cIndex = 0;

	while(	cIndex < this->colCount()
		&& !(*this)[rIndex][cIndex])
	++cIndex;

	if(cIndex == this->colCount()) {
		std::cerr << "ERROR - Matrix::pivot(...)\n";
		std::cerr << "\trow is all zeroes\n";
		return;
	}

	const double initVal = (*this)[rIndex][cIndex];
	double colVal;

	this->RO_div(rIndex, initVal);

	for(size_t j = 0;j < this->rowCount();++j) {
		if(j == rIndex) continue;
		colVal = (*this)[j][cIndex];
		if(colVal == 0.0) continue;
		this->RO_subS(j, rIndex, colVal);
	}

	this->RO_mul(rIndex, initVal);
}
