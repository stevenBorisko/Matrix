#include "Matrix.hpp"

void Matrix::destroyMatrix() {
	if(this->data) {
		for(size_t j = 0;j < this->rowCount();++j)
			if(this->data[j])
				delete[] this->data[j];
		delete[] this->data;
	}
	this->data = nullptr;
	this->row_count = 0;
	this->column_count = 0;
}
