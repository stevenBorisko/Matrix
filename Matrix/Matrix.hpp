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
	// Relational
	bool operator==(const Matrix& rhs) const;
	bool operator!=(const Matrix& rhs) const;
	// ostream
	friend std::ostream& operator<<(std::ostream& os,const Matrix& other);

	// ROW OPERATIONS

	// swap: dest <--> other
	void RO_swp(const size_t& dest, const size_t& other);
	// add: dest += other
	void RO_add(const size_t& dest, const size_t& other);
	// add constant: dest += other * scale
	void RO_addS(
		const size_t& dest,
		const size_t& other,
		const double& scale
	);
	// multiply: dest *= scale
	void RO_mul(const size_t& dest, const double& scale);
	// pivot about a row
	void RO_piv(const size_t& rIndex);
	// Row Echelon Form
	void RO_ref();
	// Reduced Row Echelon Form
	void RO_rref();

	// Trivial Functions

	// gets the number of rows in the matrix
	size_t rowCount() const;
	// gets the number of columns in the matrix
	size_t colCount() const;
	// gets deep copy of row or column p:index
	// mem must be allocated to the colCount or rowCount
	// for row and col, respectively
	double* row(double* mem, const size_t& index) const;
	double* col(double* mem, const size_t& index) const;
	// determine whether a row or column is all zeros
	bool rowZero(const size_t& index) const;
	bool colZero(const size_t& index) const;
	// get the leading coefficient of a row
	double leadCoef(const size_t& index) const;
	// gets value at row p:rIndex column p:cIndex
	double at(const size_t& rIndex, const size_t& cIndex) const;
	// sets value at row p:rIndex column p:cIndex to p:newNum
	void setAt(
		const size_t& rIndex,
		const size_t& cIndex,
		const double& newNum
	);

	// Friend

	// calculates the determinant of an m x m matrix
	friend double determinant(const Matrix& matrix);
	// TODO
	// solves for x in Ax=b where p:A is an m x m matrix
	// and p:b is an m x 1 matrix (vector)
	// returns an m x 1 matrix that represents x
	friend Matrix solve(const Matrix& A, const Matrix& b);
	// takes a matrix of vectors and returns a vector orthogonal to them
	// matrix must be m x (m-1), so, for example, you can have two columns
	// of 3-D vectors and it will return an m x 1 matrix (vector) that is
	// orthogonal to the two vectors
	friend Matrix cross(const Matrix& vecs);

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
