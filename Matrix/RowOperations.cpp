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
	size_t cIndex;
	for(cIndex = 0;cIndex < this->colCount();++cIndex)
		if((*this)[rIndex][cIndex] != 0.0)
			break;

	if(cIndex == this->colCount()) {
		std::cerr << "ERROR - RO_piv(const size_t&)\n";
		std::cerr << "\trow is all zeroes\n";
		return;
	}

	RO_piv(rIndex, cIndex);
}

void Matrix::RO_piv(const size_t& rIndex, const size_t& cIndex) {

	const double initVal = (*this)[rIndex][cIndex];
	double colVal;

	if(initVal == 0.0) {
		std::cerr << "ERROR - RO_piv(const size_t&, const size_t&)\n";
		std::cerr << "\tpivot value == 0.0\n";
		return;
	}

	this->RO_mul(rIndex, 1.0 / initVal);
	(*this)[rIndex][cIndex] = 1.0;

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
	size_t zeroRow = this->rowCount();
	size_t pivotCol;
	size_t pivotRow;

	for(	pivotRow = 0, pivotCol = 0;
		pivotRow < zeroRow && pivotCol < this->colCount();
		++pivotRow, ++pivotCol
	) {
		if(this->rowZero(pivotRow)) {
			--pivotCol;
			this->RO_swp(pivotRow--,--zeroRow);
			continue;
		}

		if((*this)[pivotRow][pivotCol] == 0.0) {
			size_t j;
			// Move j down to the next row with a non-zero
			// value in column pivotCol
			for(j = pivotRow + 1;j < zeroRow;++j)
				if((*this)[j][pivotCol] != 0.0)
					break;
			// case: there are no non-zero values below this row
			if(j == zeroRow) {
				--pivotRow;
				continue;
			}
			// case: swap this row with another
			--pivotCol;
			this->RO_swp(pivotRow--,j);
			continue;
		}
		this->RO_piv(pivotRow, pivotCol);
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
