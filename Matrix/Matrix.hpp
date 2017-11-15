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
	// multiply: dest *= other
	void RO_mul(const size_t& dest, const double& scale);
	// divide: dest /= other
	void RO_div(const size_t& dest, const double& scale);

	// Trivial Functions

	// gets the number of rows in the matrix
	size_t rowCount() const
		{ return row_count; }
	// gets the number of columns in the matrix
	size_t columnCount() const
		{ return column_count; }
	// gets shallow copy of row p:index
	double** row(const size_t& index) const
		{ return data_rows[index]; }
	// gets shallow copy of column p:index
	double** column(const size_t& index) const
		{ return data_columns[index]; }
	// gets value at row p:rIndex column p:cIndex
	double at(const size_t& rIndex, const size_t& cIndex) const
		{ return *(data_rows[rIndex][cIndex]); }
	// sets value at row p:rIndex column p:cIndex to p:newNum
	void setAt(const size_t& rIndex, const size_t& cIndex, const double& newNum)
		{ *(data_rows[rIndex][cIndex]) = newNum; }

private:

	/*
	rows -> rows of the matrix
	*rows -> list of elements in the matrix
	**rows -> address of an element in the matrix
	***rows -> element of the matrix
	*/
	double*** data_rows;

	/*
	Same concept as v:data_rows.
	This is always the transpose of data_rows, so this matrix is
	never required for functionality. It also allows individual columns
	to be retrieved which can be useful
	*/
	double*** data_columns;

	// number of rows and columns in the matrix
	size_t row_count, column_count;

	// calls destroyMatrixDeep on data_rows
	// and destroyMatrixShallow on data_columns
	void destroyMatrix();

// STATIC FUNCTIONS

	// Create

	static double*** createMatrix(
		const size_t& major,
		const size_t& minor
	);

	// Copy

	/*
	For (c/t)Matrix(D/S)(...)
		allocates a 2-D array of references to elements
		major and minor are the number of elements in (p:other)
		and *(p:other) respectively

	For (c/t)MatrixDeep(...)
		(c/t)s a matrix by allocating space for each element
		and copying the value into it

	For (c/t)MatrixShallow(...)
		(c/t)s a matrix by making copying the reference to each
		individual element
	*/

	static double*** copyMatrixDeep(
		const double*** other,
		const size_t& major,
		const size_t& minor
	);

	static double*** copyMatrixShallow(
		double*** other,
		const size_t& major,
		const size_t& minor
	);

	// Transpose

	static double*** transposeMatrixDeep(
		const double*** other,
		const size_t& major,
		const size_t& minor
	);

	static double*** transposeMatrixShallow(
		double*** other,
		const size_t& major,
		const size_t& minor
	);

	// Destroy

	/*
	For destroyMatrix(D/S)(...)
		deletes the 2-D array of references
	*/

	// deletes each referenced element
	static void destroyMatrixDeep(
		double*** other,
		const size_t& major,
		const size_t& minor
	);

	// leaves each referenced element allocated
	static void destroyMatrixShallow(
		double*** other,
		const size_t& major
	);

};

#endif
