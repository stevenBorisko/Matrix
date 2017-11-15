#include "Matrix.hpp"

Matrix::Matrix():
	data_rows(nullptr), data_columns(nullptr),
	row_count(0), column_count(0)
{ }

Matrix::Matrix(const size_t& squareDim):
	data_rows(nullptr), data_columns(nullptr),
	row_count(squareDim), column_count(squareDim)
{
	this->data_rows = Matrix::createMatrix(
		this->rowCount(), this->columnCount()
	);

	this->data_columns = Matrix::transposeMatrixShallow(
		this->data_rows, this->rowCount(), this->columnCount()
	);

	for(size_t i = 0;i < squareDim;++i)
		*(data_rows[i][i]) = 1.0;

}

Matrix::Matrix(const size_t& rowDim, const size_t& columnDim):
	data_rows(nullptr), data_columns(nullptr),
	row_count(rowDim), column_count(columnDim)
{
	this->data_rows = Matrix::createMatrix(
		this->rowCount(), this->columnCount()
	);

	this->data_columns = Matrix::transposeMatrixShallow(
		this->data_rows, this->rowCount(), this->columnCount()
	);
}

Matrix::Matrix(const Matrix& other):
	data_rows(nullptr), data_columns(nullptr),
	row_count(other.rowCount()), column_count(other.columnCount())
{

	// case trivial: other is empty
	if(!this->rowCount() || !this->columnCount()) return;

	this->data_rows = Matrix::copyMatrixDeep(
		(const double***)other.data_rows,
		other.rowCount(),
		other.columnCount()
	);

	this->data_columns = Matrix::transposeMatrixShallow(
		this->data_rows, this->rowCount(), this->columnCount()
	);

}

Matrix::~Matrix() {
	this->destroyMatrix();
}
