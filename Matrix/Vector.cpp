#include "../Matrix.hpp"

// CONSTRUCTORS

Vector::Vector(): Matrix() { }

Vector::Vector(const size_t& dim): Matrix(dim,1) { }

Vector::Vector(const Vector& other): Matrix(other) { }

Vector::Vector(const Matrix& other): Vector(other.rowCount()) {
	for(size_t i = 0;i < other.rowCount();++i)
		(*this)[i] = other[i][0];
}

Vector::~Vector() { }

// OPERATORS

double Vector::operator[](const size_t& index) const
	{ return (*this).Matrix::operator[](index)[0]; }

double& Vector::operator[](const size_t& index)
	{ return (*this).Matrix::operator[](index)[0]; }

Vector Vector::operator+(const Vector& rhs) const {
	Vector ret(*this);
	ret += rhs;
	return ret;
}

Vector Vector::operator-(const Vector& rhs) const {
	Vector ret(*this);
	ret += rhs;
	return ret;
}

Vector Vector::operator*(const double& rhs) const {
	Vector ret(*this);
	ret *= rhs;
	return ret;
}

Vector& Vector::operator+=(const Vector& rhs) {
	for(size_t i = 0;i < this->dimension();++i)
		(*this)[i] += rhs[i];
	return *this;
}

Vector& Vector::operator-=(const Vector& rhs) {
	*this += -rhs;
	return *this;
}

Vector& Vector::operator*=(const double& rhs) {
	for(size_t i = 0;i < this->dimension();++i)
		(*this)[i] *= rhs;
	return *this;
}

Vector Vector::operator-() const {
	return (*this * -1.0);
}

// FUNCTIONS

Vector Vector::subVec(const size_t& start, const size_t& dist) const {
	Vector ret(dist);
	for(size_t i = 0;i < dist;++i)
		ret[i] = (*this)[start + i];
	return ret;
}

size_t Vector::dimension() const { return this->rowCount(); }

double Vector::magnitude() const { return sqrt(abs(V_dot(*this,*this))); }

// FRIEND

Vector V_norm(const Vector& vec) { return (vec * (1.0 / vec.magnitude())); }

double V_dot(const Vector& v1, const Vector& v2) {
	return V_dot(v1, v2, v1.dimension());
}

double V_dot(
	const Vector& v1,
	const Vector& v2,
	const size_t& dim
) {
	if(v1.dimension() != v2.dimension()) {
		std::cerr << "ERROR - double Vector::dot(...)\n";
		std::cerr << "\tv1 dimension != v2 dimension\n";
		return 0.0;
	}
	double sum = 0.0;
	for(size_t i = 0;i < dim;++i)
		sum += v1[i] * v2[i];
	return sum;
}
