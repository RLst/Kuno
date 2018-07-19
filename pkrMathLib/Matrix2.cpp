//pkr Math Library
//Author: Tony Le
//Version: 1.0

#include "Matrix2.h"
#include <cmath>

namespace pkr {

const float Matrix2::DEF_TOLERANCE = 0.00001f;
const Matrix2 Matrix2::identity = Matrix2(1, 0, 0, 1);

Matrix2::Matrix2()															//Default
{
	//Initialise as an identity matrix
	*this = identity;
}

Matrix2::Matrix2(float Xx, float Xy, float Yx, float Yy)					//Initialiser
{
	data[0][0] = Xx;
	data[0][1] = Xy;
	data[1][0] = Yx;
	data[1][1] = Yy;
}

Matrix2::Matrix2(Vector2 & X, Vector2 & Y)									//Initialise by Vector
{
	xAxis = X;
	yAxis = Y;
}

Matrix2::Matrix2(const Matrix2 & other)										//Copy constructor
{
	//Copy from other into this
	for (int r = 0; r < 2; ++r)
		for (int c = 0; c < 2; ++c)
			data[r][c] = other.data[r][c];
}

Matrix2::~Matrix2()															//Destructor
{}

Vector2 & Matrix2::operator[](int index)									//Subscript mutator
{
	return axis[index];
}

const Vector2 & Matrix2::operator[](int index) const						//Subscript inspector
{
	return axis[index];
}

Matrix2 & Matrix2::operator=(const Matrix2 & other)							//Assignment
{
	for (int r = 0; r < 2; ++r) {
		for (int c = 0; c < 2; ++c) {
			data[r][c] = other.data[r][c];
		}
	}
	return *this;
}

bool Matrix2::operator==(const Matrix2 & other) const						//Equality check
{
	for (int r = 0; r < 2; ++r) {
		for (int c = 0; c < 2; ++c) {
			//If one of the elements don't match...
			if (data[r][c] != other.data[r][c])
				//It's NOT equal
				return false;
		}
	}
	return true;
}

bool Matrix2::operator!=(const Matrix2 & other) const						//Inequality check
{
	for (int r = 0; r < 2; ++r) {
		for (int c = 0; c < 2; ++c) {
			//If one of the elements do match...
			if (data[r][c] == other.data[r][c])
				//it is NOT not equal
				return false;
		}
	}
	return true;
}

bool Matrix2::equal(const Matrix2 & other, float tolerance) const			//Equality check with tolerance
{
	//If any of one the element comparisons fails, then return false
	//Otherwise all elements are all EQUAL within the specified tolerance
	for (int r = 0; r < 2; ++r)
		for (int c = 0; c < 2; ++c) {
			if (abs(data[r][c] - other.data[r][c] >= tolerance))
				return false;
		}
	return true;
}

bool Matrix2::notEqual(const Matrix2 & other, float tolerance) const		//Inequality check with tolerance
{
	//If any of one the element comparisons fails, then return false
	//Otherwise all elements are all NOT EQUAL within the specified tolerance
	for (int r = 0; r < 2; ++r)
		for (int c = 0; c < 2; ++c) {
			if (abs(data[r][c] - other.data[r][c]) < tolerance)
				return false;
		}
	return true;
}

Matrix2 Matrix2::operator+(const Matrix2 & other) const						//Addition
{
	Matrix2 result;		//Creates a seperate matrix
	for (int r = 0; r < 2; ++r)
		for (int c = 0; c < 2; ++c)
			result.data[r][c] = data[r][c] + other.data[r][c];		//Perform operation between this and other, and assign onto resultant matrix
	return result;		//Return resultant matrix
}

Matrix2 Matrix2::operator-(const Matrix2 & other) const						//Subtraction
{
	Matrix2 result;		//Creates a seperate matrix
	for (int r = 0; r < 2; ++r)
		for (int c = 0; c < 2; ++c)
			result.data[r][c] = data[r][c] - other.data[r][c];		//Perform operation between this and other, and assign onto resultant matrix
	return result;		//Return resultant matrix
}

Matrix2 & Matrix2::operator+=(const Matrix2 & other)						//Addition assign
{
	//Perform operation between this and other and return this
	for (int r = 0; r < 2; ++r) {
		for (int c = 0; c < 2; ++c) {
			data[r][c] += other.data[r][c];
		}
	}
	return *this;
}

Matrix2 & Matrix2::operator-=(const Matrix2 & other)						//Subtraction assign
{
	//Perform operation between this and other and return this
	for (int r = 0; r < 2; ++r) {
		for (int c = 0; c < 2; ++c) {
			data[r][c] -= other.data[r][c];
		}
	}
	return *this;
}

Matrix2 Matrix2::operator*(float scalar) const								//POST Scalar Multiply
{
	//Perform scalar operation on this, assign to new matrix and return
	Matrix2 result;
	for (int r = 0; r < 2; ++r)
		for (int c = 0; c < 2; ++c)
			result.data[r][c] = data[r][c] * scalar;
	return result;
}

Matrix2 Matrix2::operator/(float scalar) const								//POST Scalar Divide
{
	//Perform scalar operation on this, assign to new matrix and return
	Matrix2 result;
	for (int r = 0; r < 2; ++r)
		for (int c = 0; c < 2; ++c)
			result.data[r][c] = data[r][c] / scalar;
	return result;
}

Matrix2 operator*(float scalar, const Matrix2 & other)						//PRE Scalar Mutiply
{
	//Perform scalar operation on other, assign to new matrix and return
	Matrix2 result;
	for (int r = 0; r < 2; ++r)
		for (int c = 0; c < 2; ++c)
			result.data[r][c] = other.data[r][c] * scalar;
	return result;
}

Matrix2 & Matrix2::operator*=(float scalar)									//Scalar Multiply assign
{
	//Perform scalar operation on this and return this
	for (int r = 0; r < 2; ++r) {
		for (int c = 0; c < 2; ++c) {
			data[r][c] *= scalar;
		}
	}
	return *this;
}

Matrix2 & Matrix2::operator/=(float scalar)									//Scalar Divide assign
{
	//Perform scalar operation on this and return this
	for (int r = 0; r < 2; ++r) {
		for (int c = 0; c < 2; ++c) {
			data[r][c] /= scalar;
		}
	}
	return *this;
}

Matrix2 Matrix2::operator*(const Matrix2 & other) const						//Matrix Mutiplication
{
	//Multiply this with another matrix and return resultant
	Matrix2 result;
	for (int r = 0; r < 2; ++r) {
		for (int c = 0; c < 2; ++c) {
			result.data[c][r] = data[0][r] * other.data[c][0] +
								data[1][r] * other.data[c][1];
		}
	}
	return result;
}

Vector2 Matrix2::operator*(const Vector2 & vec) const						//Matrix to Vector Mutiplication
{
	//Multiply this with a vector and return resultant
	Vector2 result;
	for (int r = 0; r < 2; ++r) {
		result[r] = data[0][r] * vec[0] +
					data[1][r] * vec[1];
	}
	//Exploded method (faster)
	//result[0] = data[0][0] * vec[0] + data[1][0] * vec[1];
	//result[1] = data[0][1] * vec[1] + data[1][1] * vec[1];
	return result;
}

Matrix2 Matrix2::transposed() const											//Transposition
{
	//Flip row and column
	Matrix2 result;
	for (int r = 0; r < 2; ++r) {
		for (int c = 0; c < 2; ++c) {
			result.data[r][c] = data[c][r];
		}
	}
	return result;
}

Matrix2 Matrix2::createRotate(float radians)
{
	Matrix2 m;
	m.setRotate(radians);
	return m;
}

void Matrix2::setRotate(float radians)										//Set rotate
{
	//You can only rotate around the z axis in 2D so use rotate Z math?
	xAxis = { cosf(radians), sinf(radians) };
	yAxis = { -sinf(radians), cosf(radians) };
}

void Matrix2::rotate(float radians)											//Rotate
{
	//Non-member rotate
	Matrix2 m;
	m.setRotate(radians);
	*this = *this * m;
}

Matrix2 Matrix2::createScale(float x, float y)
{
	Matrix2 m;
	m.setScale(x, y);
	return m;
}

Matrix2 Matrix2::createScale(const Vector2 & vec)
{
	Matrix2 m;
	m.setScale(vec);
	return m;
}

void Matrix2::setScale(float x, float y)									//Set Scales
{
	xAxis = { x, 0 };
	yAxis = { 0, y };
}

void Matrix2::setScale(const Vector2 & vec)
{
	//Set scale by vector
	xAxis = { vec.x, 0 };
	yAxis = { 0, vec.y };
}

void Matrix2::scale(float x, float y)										//Scales
{
	Matrix2 m;
	m.setScale(x, y);
	*this = *this * m;
}

void Matrix2::scale(const Vector2 & vec)
{
	//Scale by vector
	Matrix2 m;
	m.setScale(vec);
	*this = *this * m;
}

Matrix2::operator float*()													//Mutator float cast
{
	return &data[0][0];
}

Matrix2::operator const float*() const										//Inspector float cast
{
	return &data[0][0];
}

}