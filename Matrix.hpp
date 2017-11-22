#ifndef MATRIX_H
#define MATRIX_H

#include <cstdlib>
#include <iostream>

/*
Author: Steven Borisko
Description: Matrix class that provides many standard matrix functions
*/
class Matrix {
public:

//	//	CONSTRUCTORS	//	//

	/*
	Default Constructor
	Creates an empty matrix (0 x 0)
	*/
	Matrix();
	/*
	param	squareDim	(const size_t&)
		number of rows and columns in the square matrix

	Custom Constructor: Square
	Creates an (m x m) identity matrix
	*/
	Matrix(const size_t& squareDim);
	/*
	param	rowDim		(const size_t&)
		number of rows in the matrix
	param	columnDim	(const size_t&)
		number of columns in the matrix

	Custom Constructor: (m x n) dimension matrix
	Creates an (m x n) matrix of all zeroes
	*/
	Matrix(const size_t& rowDim, const size_t& columnDim);
	/*
	param	other		(const Matrix&)
		matrix to be copied into this matrix

	Copy Constructor: deep copy
	*/
	Matrix(const Matrix& other);
	/*
	Destructor
	Frees data by calling destroyMatrix();
	*/
	~Matrix();

//	//	OPERATORS	//	//

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

//	//	ROW OPERATIONS	//	//

	/*
	param	dest		(const size_t&)
		one of the rows to swap
	param	other		(const size_t&)
		the other row to swap

	Swap rows
	dest <=> other
	*/
	void RO_swp(const size_t& dest, const size_t& other);
	/*
	param	dest		(const size_t&)
		row that will hold the sum
	param	other		(const size_t&)
		row that will be added to row p:dest

	Add row
	dest += other
	*/
	void RO_add(const size_t& dest, const size_t& other);
	/*
	param	dest		(const size_t&)
		row that will hold the sum
	param	other		(const size_t&)
		row that will be scaled and added to p:dest
	param	scale		(const size_t&)
		scaling factor that will be applied to p:other

	Add row (Scalar)
	dest += other * scale
	*/
	void RO_addS(
		const size_t& dest,
		const size_t& other,
		const double& scale
	);
	/*
	param	dest		(const size_t&)
		row to be scaled
	param	scale		(const double&)
		scaling factor of row p:dest

	Scale row
	dest *= scale
	*/
	void RO_mul(const size_t& dest, const double& scale);
	/*
	param	rIndex		(const size_t&)
		index of the row about which the matrix will be pivotted

	Pivot
	Pivot about a row at its first non-zero column
	*/
	void RO_piv(const size_t& rIndex);
	/*
	param	rIndex		(const size_t&)
		index of the row about which the matrix will be pivotted
	param	cIndex		(const size_t&)
		index of the column about which the matrix will be pivotted

	Pivot
	Pivot about a given row and column
	*/
	void RO_piv(const size_t& rIndex, const size_t& cIndex);
	/*
	Row Echelelon Form
	Performs row operations to transform the matrix into row echelon form
	*/
	void RO_ref();
	/*
	Reduced Row Echelon Form
	Performs row operations to transform the matrix into reduced row echelon form
	*/
	void RO_rref();

//	//	TRIVIAL FUNCTIONS	//

	/*
	returns			(size_t)
		number of rows in the matrix

	Row Count
	gets the number of rows in the matrix by returning v:row_count
	*/
	size_t rowCount() const;
	/*
	returns			(size_t)
		number of columns in the matrix

	Row Count
	gets the number of columns in the matrix by returning v:col_count
	*/
	size_t colCount() const;
	/*
	param	mem		(double*)
		memory for the row/col to be copied into
	param	index		(const size_t&)
		index of the row/col to be copied
	returns			(double*)
		p:mem

	Get Row/Column
	Performs a deep copy of a row/column into p:mem
	*/
	double* row(double* mem, const size_t& index) const;
	double* col(double* mem, const size_t& index) const;
	/*
	param	index		(const size_t&)
		index of the row/col to be inspected
	returns			(bool)
		whether the row/column is all zeroes

	Row/Column is Zeroes
	Determines whether the row/column consists of solely zeroes
	*/
	bool rowZero(const size_t& index) const;
	bool colZero(const size_t& index) const;
	/*
	param	index		(const size_t&)
		index of the row to inspect
	returns			(double)
		the leading coefficient of row p:index

	Get Leading Coefficient of a Row
	Gets the first non-zero element in row p:index
	*/
	double leadCoef(const size_t& index) const;
	/*
	param	index		(const size_t&)
		index of the row to inspect
	returns			(double)
		the index of the leading coefficient of row p:index

	Index of the Leading Coefficient of a Row
	*/
	size_t leadIndex(const size_t& index) const;
	/*
	Reduce Floating Point Error
	Calls almostZero(const double&) on every element in the matrix.
	If it returns true, the value is set to zero.
	*/
	void reduceFPE();
	/*
	param	rIndex		(const size_t&)
		index of the row from which data will be retrieved
	param	cIndex		(const size_t&)
		index of the column from which data will be retrieved
	returns			(double)
		the element at p:rIndex,p:cIndex

	Get Element At
	Gets the element at a given row and column
	*/
	double at(const size_t& rIndex, const size_t& cIndex) const;
	/*
	param	rIndex		(const size_t&)
		index of the row to which data will be set
	param	cIndex		(const size_t&)
		index of the column to which data will be set
	param	newNum		(const double&)
		data to which the element at p:rIndex,p:cIndex will be set

	Set Element At
	Sets the element at a given row and column
	*/
	void setAt(
		const size_t& rIndex,
		const size_t& cIndex,
		const double& newNum
	);

//	//	FRIEND		//	//

	/*
	param	matrix		(const Matrix&)
		matrix from which the determinant will be calculated
	returns			(double)
		the determinant of the matrix

	Get Determinant
	Calculates the determinant of a matrix
	*/
	friend double M_determinant(const Matrix& matrix);
	/*
	param	vecs		(const Matrix&)
		matrix of vectors
	returns			(Matrix)
		the cross product of the vectors in p:vecs

	Cross product
	Takes a matrix of vectors and returns a vector orthogonal to all of them.
	p:vecs must be m x (m-1), so for example, you can have two columns of 3-D
	vectors and it will return a 3 x 1 matrix (vector) that is orthogonal to
	the two vectors.
	*/
	friend Matrix M_cross(const Matrix& vecs);
	/*
	param	matrix		(const Matrix&)
		matrix from which the rank will be determined
	returns			(size_t)
		rank of matrix p:matrix

	Get Rank
	Calculates the rank of a p:matrix assuming it is in REF
	*/
	friend size_t M_rank(const Matrix& matrix);
	/*
	param	matrix		(const Matrix&)
		matrix to inspect
	returns			(bool)
		whether matrix p:matrix is full rank

	Matrix is full rank
	Determines whether a matrix is full rank assuming it is in REF
	*/
	friend bool M_fullRank(const Matrix& matrix);
	/*
	param	matrix		(const Matrix&)
		matrix to invert
	returns			(Matrix)
		the inverse of matrix p:matrix

	Get Inverse
	Calculates the inverse of a matrix
	*/
	friend Matrix M_inverse(const Matrix& matrix);

//	//	PRIVATE		//	//
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

//	//	STATIC		//	//

	// allocates space for and zeroes out a 2-D matrix
	// of p:rows rows and p:cols columns
	// this is solely needed for constructors and operator=
	static double** createMatrix(const size_t& rows, const size_t& cols) {
		double** ret = new double*[rows];
		for(size_t j = 0;j < rows;++j) {
			ret[j] = new double[cols];
			for(size_t i = 0;i < cols;++i)
				ret[j][i] = 0.0;
		}
		return ret;
	}

	// almost* is used to reduce floating point error
	static bool almostZero(const double& a) {
		return Matrix::almostEquals(a,0.0);
	}

	static bool almostInt(const double& a) {
		return Matrix::almostEquals(a, (double)(int)a);
	}

	static bool almostEquals(const double& a, const double& b) {
		const double bound = 0.0000000001;
		double diff = a - b;
		return (-bound < diff) && (diff < bound);
	}

};

#endif
