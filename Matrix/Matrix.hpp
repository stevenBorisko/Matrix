#ifndef MATRIX_H
#define MATRIX_H

#include <cstdlib>
#include <iostream>

/*
Matrix class that provides many standard matrix functions
Not very memory efficient, so don't make huge matrices or a bunch of them
*/
class Matrix {
public:

	// CONSTRUCTORS

	// default: empty matrix (0x0)
	Matrix();
	// custom: identity matrix of dimension p:squareDim
	Matrix(const size_t& squareDim);
	// custom: zero matrix of dimension p:rowDim x p:columnDim
	Matrix(const size_t& rowDim, const size_t& columnDim);
	// copy: deep
	Matrix(const Matrix& other);
	// destructor
	~Matrix();

	// OPERATORS

	// Assignment
	Matrix& operator=(const Matrix& rhs);
	double* operator[](const size_t& rIndex) const;
	double* operator[](const size_t& rIndex);
	// Binary
	Matrix operator+(const Matrix& rhs) const;
	Matrix operator-(const Matrix& rhs) const;
	Matrix operator*(const Matrix& rhs) const;
	Matrix operator*(const double& rhs) const;
	// Binary Assignment
	Matrix& operator+=(const Matrix& rhs);
	Matrix& operator-=(const Matrix& rhs);
	Matrix& operator*=(const Matrix& rhs);
	Matrix& operator*=(const double& rhs);
	// Unary
	Matrix operator-() const;
		// transpose
	Matrix operator~() const;
	// ostream
	friend std::ostream& operator<<(std::ostream& os,const Matrix& other);

	// ROW OPERATIONS

	// swap: dest <--> other
	void RO_swp(const size_t& dest, const size_t& other);
	// add: dest += other
	void RO_add(const size_t& dest, const size_t& other);
	// subtract: dest -= other
	void RO_sub(const size_t& dest, const size_t& other);
	// multiply: dest *= scale
	void RO_mul(const size_t& dest, const double& scale);
	// divide: dest /= scale
	void RO_div(const size_t& dest, const double& scale);

	// Trivial Functions

	// gets the number of rows in the matrix
	size_t rowCount() const;
	// gets the number of columns in the matrix
	size_t colCount() const;
	// gets deep copy of row p:index; allocs array
	double* row(const size_t& index) const;
	// gets deep copy of column p:index;; allocs array
	double* col(const size_t& index) const;
	// gets value at row p:rIndex column p:cIndex
	double at(const size_t& rIndex, const size_t& cIndex) const;
	// sets value at row p:rIndex column p:cIndex to p:newNum
	void setAt(
		const size_t& rIndex,
		const size_t& cIndex,
		const double& newNum
	);

private:

	double** data;

	// number of rows and columns in the matrix
	size_t row_count, col_count;

	// set the row and column count
	// use with caution
	void setRowCount(const size_t& newRC) { this->row_count = newRC; }
	void setColCount(const size_t& newCC) { this->col_count = newCC; }

	// frees v:data
	void destroyMatrix();

	// allocates space for and zeroes out a 2-D matrix
	// of p:rows rows and p:cols columns
	static double** createMatrix(const size_t& rows, const size_t& cols) {
		double** ret = new double*[rows];
		for(size_t j = 0;j < rows;++j) {
			ret[j] = new double[cols];
			for(size_t i = 0;i < cols;++i)
				ret[j][i] = 0.0;
		}
		return ret;
	}

};

#endif
