#include "Matrix.hpp"

void Matrix::destroyMatrix() {
	Matrix::destroyMatrixDeep(data_rows,this->rowCount(),this->columnCount());
	Matrix::destroyMatrixShallow(data_columns,this->columnCount());
	this->data_rows = nullptr;
	this->data_columns = nullptr;
	this->row_count = 0;
	this->column_count = 0;
}
