#include "Matrix.hpp"

void Matrix::RO_swp(const size_t& dest, const size_t& other) {
	double temp;
	for(size_t col = 0;col < this->colCount();++col) {
		temp = this->at(dest, col);
		this->setAt(dest, col, this->at(other, col));
		this->setAt(other, col, temp);
	}
}

void Matrix::RO_add(const size_t& dest, const size_t& other) {
	for(size_t col = 0;col < this->colCount();++col)
		this->setAt(dest,col,this->at(dest,col) + this->at(other, col));
}

void Matrix::RO_sub(const size_t& dest, const size_t& other) {
	if(dest == other) {
		std::cerr << "ERROR - Matrix::RO_mul(...)\n";
		std::cerr << "\tdest == other\n";
		return;
	}
	for(size_t col = 0;col < this->colCount();++col)
		this->setAt(dest,col,this->at(dest,col) - this->at(other, col));
}

void Matrix::RO_mul(const size_t& dest, const double& scale) {
	if(scale == 0.0) {
		std::cerr << "ERROR - Matrix::RO_mul(...)\n";
		std::cerr << "\tscale == 0\n";
		return;
	}
	for(size_t col = 0;col < this->colCount();++col)
		this->setAt(dest,col,this->at(dest,col) * scale);
}

void Matrix::RO_div(const size_t& dest, const double& scale) {
	if(scale == 0.0) {
		std::cerr << "ERROR - Matrix::RO_div(...)\n";
		std::cerr << "\tscale == 0\n";
		return;
	}
	for(size_t col = 0;col < this->colCount();++col)
		this->setAt(dest,col,this->at(dest,col) / scale);
}
