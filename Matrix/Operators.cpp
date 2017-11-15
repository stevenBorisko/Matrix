#include "Matrix.hpp"

	// Assignment
Matrix& Matrix::Matrix::operator=(const Matrix& rhs) {

	// case trivial: same objects
	if(this == &rhs) return *this;

	// if the dimensions of the two matrices are unequal,
	// make new arrays for this matrix
	if(
		(this->rowCount() != rhs.rowCount())
		|| (this->columnCount() != rhs.columnCount())
	)	{

		this->destroyMatrix();

		this->row_count = rhs.rowCount();
		this->column_count = rhs.columnCount();

		// case other is empty
		if(!this->rowCount() || !this->columnCount()) {
			this->row_count = 0;
			this->column_count = 0;
			return *this;
		}

		this->data_rows = Matrix::copyMatrixDeep(
			(const double***)rhs.data_rows,
			rhs.rowCount(),
			rhs.columnCount()
		);

		this->data_columns = Matrix::transposeMatrixShallow(
			this->data_rows, this->rowCount(), this->rowCount()
		);

		return *this;
	}

	// case this is empty meaning rhs is empty
	if(!this->rowCount() || !this->columnCount()) return *this;

	// At this point, data_rows and data_columns exist and aren't empty
	// for this and the dimensions are the same for both objects

	// copy rhs.data into this->data
	for(size_t j = 0;j < this->rowCount();++j)
		for(size_t i = 0;i < this->columnCount();++i)
			this->setAt(j,i,*rhs.data_rows[j][i]);

	return *this;
}

	// Binary

Matrix Matrix::operator+(const Matrix& rhs) const {
	Matrix ret = *this;
	ret += rhs;
	return ret;
}

Matrix Matrix::operator-(const Matrix& rhs) const {
	Matrix ret = *this;
	ret -= rhs;
	return ret;
}

Matrix Matrix::operator*(const Matrix& rhs) const {
	Matrix ret = *this;
	ret *= rhs;
	return ret;
}

Matrix Matrix::operator*(const double& rhs) const {
	Matrix ret = *this;
	ret *= rhs;
	return ret;
}

	// Binary Assignment

Matrix& Matrix::operator+=(const Matrix& rhs) {
	if(	this->rowCount() != rhs.rowCount()
		|| this->columnCount() != rhs.columnCount()
	) {
		std::cerr << "ERROR - Matrix::operator+=(const Matrix& rhs)\n";
		std::cerr << "\tthis dimensions != rhs dimensions\n";
		return *this;
	}
	for(size_t j = 0;j < this->rowCount();++j)
		for(size_t i = 0;i < this->columnCount();++i)
			this->setAt(j, i, this->at(j,i) + rhs.at(j,i));
	return *this;
}

Matrix& Matrix::operator-=(const Matrix& rhs) {
	if(	this->rowCount() != rhs.rowCount()
		|| this->columnCount() != rhs.columnCount()
	) {
		std::cerr << "ERROR - Matrix::operator-=(const Matrix& rhs)\n";
		std::cerr << "\tthis dimensions != rhs dimensions\n";
		return *this;
	}
	for(size_t j = 0;j < this->rowCount();++j)
		for(size_t i = 0;i < this->columnCount();++i)
			this->setAt(j, i, this->at(j,i) - rhs.at(j,i));
	return *this;
}

Matrix& Matrix::operator*=(const Matrix& rhs) {
	if(	this->rowCount() != rhs.rowCount()
		|| this->columnCount() != rhs.columnCount()
	) {
		std::cerr << "ERROR - Matrix::operator*=(const Matrix& rhs)\n";
		std::cerr << "\tthis dimensions != rhs dimensions\n";
		return *this;
	}

	Matrix temp = Matrix(*this);
	*this = Matrix(this->rowCount(), rhs.columnCount());

	for(size_t outCol = 0;outCol < rhs.columnCount();++outCol) {
		for(size_t row = 0;row < temp.rowCount();++row) {
			double sum = 0.0;
			for(size_t inCol = 0;inCol < temp.columnCount();++inCol) {
				sum += temp.at(row,inCol) * rhs.at(inCol,outCol);
			}
			this->setAt(row,outCol,sum);
		}
	}

	return *this;
}

Matrix& Matrix::operator*=(const double& rhs) {
	for(size_t j = 0;j < this->rowCount();++j)
		for(size_t i = 0;i < this->columnCount();++i)
			this->setAt(j, i, this->at(j,i) * rhs);
	return *this;
}

	// Unary

Matrix Matrix::operator-() const {
	return *this * -1.0;
}

Matrix Matrix::operator~() const {
	Matrix ret = Matrix(*this);
	double*** temp_data;
	size_t temp_count;

	// swap columns and rows
	temp_data = ret.data_rows;
	ret.data_rows = ret.data_columns;
	ret.data_columns = temp_data;

	temp_count = ret.row_count;
	ret.row_count = ret.column_count;
	ret.column_count = temp_count;

	return ret;
}

	// ostream

std::ostream& operator<<(std::ostream& os, const Matrix& other) {
	os << "[ <Matrix>\n";
	size_t lastRow = other.rowCount() - 1;
	size_t lastColumn = other.columnCount() - 1;
	// print all but the last row
	for(size_t j = 0;j < lastRow;++j) {
		os << "[";
		// print all but the last column
		for(size_t i = 0;i < lastColumn;++i)
			os << "\t" << other.at(j,i) << ",";
		// print last column
		os << "\t" << other.at(j,lastColumn) << "],\n";
	}
	// print last row
	os << "[";
	// print all but the last column
	for(size_t i = 0;i < lastColumn;++i)
		os << "\t" << other.at(lastRow,i) << ",";
	// print last column
	os << "\t" << other.at(lastRow,lastColumn) << "]\n";
	return os << "] </Matrix>";
}
