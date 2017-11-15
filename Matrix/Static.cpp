#include "Matrix.hpp"

	// Create

double*** Matrix::createMatrix(
	const size_t& major,
	const size_t& minor
) {
	double*** ret = new double**[major];
	for(size_t i = 0;i < major;++i) {
		ret[i] = new double*[minor];
		for(size_t j = 0;j < minor;++j)
			ret[i][j] = new double(0.0);
	}
	return ret;
}

	// Copy

double*** Matrix::copyMatrixDeep(
	const double*** other,
	const size_t& major,
	const size_t& minor
) {
	double*** ret = new double**[major];
	for(size_t i = 0;i < major;++i) {
		ret[i] = new double*[minor];
		for(size_t j = 0;j < minor;++j)
			ret[i][j] = new double(*other[i][j]);
	}
	return ret;
}

double*** Matrix::copyMatrixShallow(
	double*** other,
	const size_t& major,
	const size_t& minor
) {
	double*** ret = new double**[major];
	for(size_t i = 0;i < major;++i) {
		ret[i] = new double*[minor];
		for(size_t j = 0;j < minor;++j)
			ret[i][j] = other[i][j];
	}
	return ret;
}

	// Transpose

double*** Matrix::transposeMatrixDeep(
	const double*** other,
	const size_t& major,
	const size_t& minor
) {
	double*** ret = new double**[minor];
	for(size_t i = 0;i < minor;++i) {
		ret[i] = new double*[major];
		for(size_t j = 0;j < major;++j)
			ret[i][j] = new double(*other[j][i]);
	}
	return ret;
}

double*** Matrix::transposeMatrixShallow(
	double*** other,
	const size_t& major,
	const size_t& minor
) {
	double*** ret = new double**[minor];
	for(size_t i = 0;i < minor;++i) {
		ret[i] = new double*[major];
		for(size_t j = 0;j < major;++j)
			ret[i][j] = other[j][i];
	}
	return ret;
}

	// Destroy

void Matrix::destroyMatrixDeep(
	double*** other,
	const size_t& major,
	const size_t& minor
) {
	if(!other) return;
	for(size_t i = 0;i < major;++i) {
		if(!other[i]) continue;
		for(size_t j = 0;j < minor;++j) {
			if(!other[i][j]) continue;
			delete other[i][j];
		}
		delete[] other[i];
	}
	delete[] other;
}

void Matrix::destroyMatrixShallow(
	double*** other,
	const size_t& major
) {
	if(!other) return;
	for(size_t i = 0;i < major;++i) {
		if(!other[i]) continue;
		delete[] other[i];
	}
	delete[] other;
}
