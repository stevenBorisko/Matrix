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

void Matrix::RO_mul(const size_t& dest, const double& scale) {
	if(scale == 0.0) {
		std::cerr << "ERROR - Matrix::RO_mul(...)\n";
		std::cerr << "\tscale == 0\n";
		return;
	}
	for(size_t col = 0;col < this->colCount();++col)
		(*this)[dest][col] = ((*this)[dest][col] * scale) + 0.0;
}

void Matrix::RO_piv(const size_t& rIndex) {
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

	this->RO_mul(rIndex, 1.0 / initVal);

	for(size_t j = 0;j < this->rowCount();++j) {
		if(j == rIndex) continue;
		colVal = (*this)[j][cIndex];
		if(colVal == 0.0) continue;
		colVal = -colVal;
		this->RO_addS(j, rIndex, colVal);
	}

	this->RO_mul(rIndex, initVal);
}

void Matrix::RO_ref() {
	size_t zeroRow = this->colCount();
	for(size_t row = 0;row < zeroRow;++row) {
		if(this->rowZero(row)) {
			this->RO_swp(row--,--zeroRow);
			continue;
		}
		this->RO_piv(row);
	}
}

void Matrix::RO_rref() {
	this->RO_ref();
	size_t row;
	for(size_t rowPO = this->rowCount();rowPO > 0;--rowPO) {
		row = rowPO - 1;
		if(this->rowZero(row)) continue;
		double scale = 1.0 / (this->leadCoef(row));
		this->RO_mul(row, scale);
		this->RO_piv(row);
	}
}
