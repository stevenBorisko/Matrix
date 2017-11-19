#include "Matrix.hpp"

double M_determinant(const Matrix& matrix) {
	if(matrix.rowCount() != matrix.colCount()) {
		std::cerr << "ERROR - double M_determinant(const Matrix&)\n";
		std::cerr << "\tmatrix is not square\n";
		return 0.0;
	}
	if(!matrix.rowCount()) {
		std::cerr << "ERROR - double M_determinant(const Matrix&)\n";
		std::cerr << "\tmatrix empty\n";
		return 0.0;
	}
	// base case
	if(matrix.rowCount() == 1) return matrix[0][0];

	Matrix sub = Matrix(matrix.rowCount() - 1);

	double ret = 0.0;
	double subDet;

	for(size_t i = 0;i < matrix.colCount();++i) {
		// if it's zero, go to the next one
		if(matrix[0][i] == 0) continue;

		// set up matrix sub for determinant
		size_t subCol = 0;
		for(;subCol < i;++subCol) {
			for(size_t k = 0;k < sub.colCount();++k)
				sub[k][subCol] = matrix[k+1][subCol];
		}
		for(;subCol < sub.colCount();++subCol) {
			for(size_t k = 0;k < sub.colCount();++k)
				sub[k][subCol] = matrix[k+1][subCol+1];
		}
		subDet = matrix[0][i] * M_determinant(sub);
		if(i & 1) ret -= subDet;
		else ret += subDet;
	}
	return ret;
}

Matrix M_cross(const Matrix& vecs) {
	if(vecs.rowCount() != vecs.colCount() + 1) {
		std::cerr << "ERROR - Matrix cross(const Matrix& vecs)\n";
		std::cerr << "\tinvalid dimensions\n";
		return Matrix();
	}
	Matrix ret(vecs.rowCount(),1);
	Matrix sub(vecs.colCount());
	for(size_t i = 0;i < vecs.rowCount();++i) {

		size_t subRow = 0;
		for(;subRow < i;++subRow) {
			for(size_t k = 0;k < sub.colCount();++k)
				sub[subRow][k] = vecs[subRow][k];
		}
		for(;subRow < sub.colCount();++subRow) {
			for(size_t k = 0;k < sub.colCount();++k)
				sub[subRow][k] = vecs[subRow+1][k];
		}

		std::cerr << "sub matrix:\n" << sub << "\n";

		ret[i][0] = M_determinant(sub);
		if(i & 1) ret[i][0] = (ret[i][0] * -1.0) + 0.0;
	}

	return ret;
}

size_t M_rank(const Matrix& matrix) {
	size_t row;
	for(row = 0;row < matrix.rowCount();++row)
		if(matrix.rowZero(row))
			return row;
	return row;
}

bool M_fullRank(const Matrix& matrix) {
	size_t minDim = matrix.rowCount();
	if(matrix.colCount() < minDim) minDim = matrix.colCount();
	return M_rank(matrix) == minDim;
}
