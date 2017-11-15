#include "Matrix.hpp"

Matrix::Matrix():
	data(nullptr), row_count(0), col_count(0)
{ }

Matrix::Matrix(const size_t& squareDim):
	data(nullptr), row_count(squareDim), col_count(squareDim)
{
	if(!squareDim) return;
	data = Matrix::createMatrix(this->rowCount(), this->colCount());
	// make this an identity matrix
	for(size_t i = 0;i < squareDim;++i)
		data[i][i] = 1.0;
}

Matrix::Matrix(const size_t& rowDim, const size_t& columnDim):
	data(nullptr), row_count(rowDim), col_count(columnDim)
{
	if(!this->rowCount() || !this->colCount()) return;
	data = Matrix::createMatrix(this->rowCount(), this->colCount());
}

Matrix::Matrix(const Matrix& other):
	data(nullptr),
	row_count(other.rowCount()), col_count(other.colCount())
{
	// case trivial: other is empty
	if(!this->rowCount() || !this->colCount()) return;

	data = Matrix::createMatrix(this->rowCount(), this->colCount());
	for(size_t j = 0;j < this->rowCount();++j)
		for(size_t i = 0;i < this->colCount();++i)
			data[j][i] = other.data[j][i];
}

Matrix::~Matrix() {
	this->destroyMatrix();
}
