//pkr Math Library
//Author: Tony Le
//Version: 1.0

#include "Matrix3.h"
#include <cmath>

namespace pkr {

const float Matrix3::DEF_TOLERANCE = 0.00001f;
const Matrix3 Matrix3::identity = Matrix3(	1, 0, 0, 
											0, 1, 0, 
											0, 0, 1);

Matrix3::Matrix3()												//Default
{
	//Initialise as an identity matrix
	*this = identity;
	////Clear the matrix
	//xAxis = { 0, 0, 0 };
	//yAxis = { 0, 0, 0 };
	//zAxis = { 0, 0, 0 };
}

Matrix3::Matrix3(float Xx, float Xy, float Xz,					//Init
				 float Yx, float Yy, float Yz, 
				 float Zx, float Zy, float Zz)
{
	xAxis.x = Xx; xAxis.y = Xy; xAxis.z = Xz;
	yAxis.x = Yx; yAxis.y = Yy; yAxis.z = Yz;
	zAxis.x = Zx; zAxis.y = Zy; zAxis.z = Zz;
}

Matrix3::Matrix3(Vector3 & X, Vector3 & Y, Vector3 & Z)			//Init by vector
{
	xAxis = X;
	yAxis = Y;
	zAxis = Z;
}

Matrix3::Matrix3(const Matrix3 & other)							//Copy
{
	//Copy from other into this
	for (int r = 0; r < 3; ++r)
		for (int c = 0; c < 3; ++c)
			data[r][c] = other.data[r][c];
}

Matrix3::~Matrix3()												//Destructor
{}

Vector3 & Matrix3::operator[](int index)						//Subscript mutator
{
	return axis[index];
}

const Vector3 & Matrix3::operator[](int index) const			//Subscript inspector
{
	return axis[index];
}

Matrix3 & Matrix3::operator=(const Matrix3 & other)				//Assignment
{
	for (int r = 0; r < 3; ++r)
		for (int c = 0; c < 3; ++c)
			data[r][c] = other.data[r][c];
	return *this;
}

bool Matrix3::operator==(const Matrix3 & other) const			//Equality check
{
	for (int r = 0; r < 3; ++r)
		for (int c = 0; c < 3; ++c)
			if (data[r][c] != other.data[r][c])
				return false;	//Something is NOT EQUAL so return false
	return true;	//All EQUAL
}

bool Matrix3::operator!=(const Matrix3 & other) const			//Inequality check
{
	for (int r = 0; r < 3; ++r)
		for (int c = 0; c < 3; ++c)
			if (data[r][c] == other.data[r][c])
				return false;	//Something is NOT NOT EQUAL so return false
	return true;	//All NOT EQUAL
}

bool Matrix3::equal(const Matrix3 & other, float tolerance) const	//Equality check with tolerance
{
	//If any of one the element comparisons fails, then return false
	//Otherwise all elements are all EQUAL within the specified tolerance
	for (int r = 0; r < 3; ++r)
		for (int c = 0; c < 3; ++c) {
			if (abs(data[r][c] - other.data[r][c] >= tolerance))
				return false;
		}
	return true;
}

bool Matrix3::notEqual(const Matrix3 & other, float tolerance) const	//Inequality check with tolerance
{
	//If any of one the element comparisons fails, then return false
	//Otherwise all elements are all NOT EQUAL within the specified tolerance
	for (int r = 0; r < 3; ++r)
		for (int c = 0; c < 3; ++c) {
			if (abs(data[r][c] - other.data[r][c]) < tolerance)
				return false;
		}
	return true;
}

Matrix3 Matrix3::operator+(const Matrix3 & other) const
{
	Matrix3 result;		//Creates a seperate matrix
	for (int r = 0; r < 3; ++r)
		for (int c = 0; c < 3; ++c)
			result.data[r][c] =  data[r][c] + other.data[r][c];		//Perform operation between this and other, and assign onto resultant matrix
	return result;		//Return resultant matrix
}

Matrix3 Matrix3::operator-(const Matrix3 & other) const
{
	Matrix3 result;		//Creates a seperate matrix
	for (int r = 0; r < 3; ++r)
		for (int c = 0; c < 3; ++c)
			result.data[r][c] = data[r][c] - other.data[r][c];		//Perform operation between this and other, and assign onto resultant matrix
	return result;		//Return resultant matrix
}

Matrix3 & Matrix3::operator+=(const Matrix3 & other)
{
	//Perform operation between this and other and return this
	for (int r = 0; r < 3; ++r) {
		for (int c = 0; c < 3; ++c) {
			data[r][c] += other.data[r][c];
		}
	}
	return *this;
}

Matrix3 & Matrix3::operator-=(const Matrix3 & other)
{
	//Perform operation between this and other and return this
	for (int r = 0; r < 3; ++r) {
		for (int c = 0; c < 3; ++c) {
			data[r][c] -= other.data[r][c];
		}
	}
	return *this;
}

Matrix3 Matrix3::operator*(float scalar) const
{
	//Perform scalar operation on this, assign to new matrix and return
	Matrix3 result;
	for (int r = 0; r < 3; ++r)
		for (int c = 0; c < 3; ++c)
			result.data[r][c] = data[r][c] * scalar;
	return result;
}

Matrix3 Matrix3::operator/(float scalar) const
{
	//Perform scalar operation on this, assign to new matrix and return
	Matrix3 result;
	for (int r = 0; r < 3; ++r)
		for (int c = 0; c < 3; ++c)
			result.data[r][c] = data[r][c] / scalar;
	return result;
}

Matrix3 operator*(float scalar, const Matrix3 & other)
{
	//Perform scalar operation on other, assign to new matrix and return
	Matrix3 result;
	for (int r = 0; r < 3; ++r)
		for (int c = 0; c < 3; ++c)
			result.data[r][c] = other.data[r][c] * scalar;
	return result;
}

Matrix3 & Matrix3::operator*=(float scalar)
{
	//Perform scalar operation on this and return this
	for (int r = 0; r < 3; ++r) {
		for (int c = 0; c < 3; ++c) {
			data[r][c] *= scalar;
		}
	}
	return *this;
}

Matrix3 & Matrix3::operator/=(float scalar)
{
	//Perform scalar operation on this and return this
	for (int r = 0; r < 3; ++r) {
		for (int c = 0; c < 3; ++c) {
			data[r][c] /= scalar;
		}
	}
	return *this;
}

Matrix3 Matrix3::operator*(const Matrix3 & other) const
{
	//Multiply this with non-member matrix and return resultant
	Matrix3 result;
	for (int r = 0; r < 3; ++r) {
		for (int c = 0; c < 3; ++c) {
			result.data[c][r] = data[0][r] * other.data[c][0] +
								data[1][r] * other.data[c][1] +
								data[2][r] * other.data[c][2];
		}
	}
	return result;
}

Vector3 Matrix3::operator*(const Vector3 & vec) const
{
	//Multiply this with non-member vector and return resultant
	Vector3 result;
	for (int r = 0; r < 3; ++r) {
		result[r] = data[0][r] * vec[0] +
					data[1][r] * vec[1] +
					data[2][r] * vec[2];
	}
	return result;
}

Matrix3 Matrix3::transposed() const
{
	//Flip row and column
	Matrix3 result;
	for (int r = 0; r < 3; ++r) {
		for (int c = 0; r < 3; ++c) {
			result.data[r][c] = data[c][r];
		}
	}
	return result;
}

Matrix3 Matrix3::createTranslate(float x, float y)
{
	Matrix3 m;
	m.setTranslate(x, y);
	return m;
}

Matrix3 Matrix3::createTranslate(const Vector3 & vec)
{
	Matrix3 m;
	m.setTranslate(vec.x, vec.y);
	return m;
}

void Matrix3::setTranslate(float x, float y)
{
	//Set translation axis
	translation = { x, y, 0 };
}

void Matrix3::translate(float x, float y)
{
	//Modify translation axis
	translation += { x, y, 0 };
}

void Matrix3::translate(const Vector3 & vec)
{
	//Apply vector offset
	translation += vec;
}

Matrix3 Matrix3::createRotateX(float radians)
{
	Matrix3 m;
	m.setRotateX(radians);
	return m;
}

Matrix3 Matrix3::createRotateY(float radians)
{
	Matrix3 m;
	m.setRotateY(radians);
	return m;
}

Matrix3 Matrix3::createRotateZ(float radians)
{
	Matrix3 m;
	m.setRotateZ(radians);
	return m;
}

void Matrix3::setRotateX(float radians)
{
	//Leave X axis and elements unchanged
	xAxis = { 1, 0, 0 };
	yAxis = { 0 , cosf(radians), sinf(radians) };
	zAxis = { 0 , -sinf(radians), cosf(radians) };
}

void Matrix3::setRotateY(float radians)
{
	//Leave Y axis and elements unchanged
	xAxis = { cosf(radians), 0, -sinf(radians) };
	yAxis = { 0, 1, 0 };
	zAxis = { sinf(radians), 0, cosf(radians) };
}

void Matrix3::setRotateZ(float radians)
{
	//Leave Z axis and elements unchanged
	xAxis = { cosf(radians), sinf(radians), 0 };
	yAxis = { -sinf(radians), cosf(radians), 0 };
	zAxis = { 0, 0, 1 };
}

void Matrix3::rotateX(float radians)			//Non-member rotates
{
	Matrix3 m;
	m.setRotateX(radians);
	*this = *this * m;
}

void Matrix3::rotateY(float radians)
{
	Matrix3 m;
	m.setRotateY(radians);
	*this = *this * m;
}

void Matrix3::rotateZ(float radians)
{
	Matrix3 m;
	m.setRotateZ(radians);
	*this = *this * m;
}

void Matrix3::setEuler(float pitch, float yaw, float roll)
{
	Matrix3 x, y, z;
	y.setRotateX(pitch);
	y.setRotateY(yaw);
	z.setRotateZ(roll);
	//Combine rotations in a specific order
	*this = z * y * x;
}

Matrix3 Matrix3::createScale(float x, float y, float z)
{
	Matrix3 m;
	m.setScale(x, y, z);
	return m;
}

Matrix3 Matrix3::createScale(const Vector3 & vec)
{
	Matrix3 m;
	m.setScale(vec.x, vec.y, vec.z);
	return m;
}

void Matrix3::setScale(float x, float y, float z)
{
	//Set scale of each axis
	xAxis = { x, 0, 0 };
	yAxis = { 0, y, 0 };
	zAxis = { 0, 0, z };
}

void Matrix3::scale(float x, float y, float z)
{
	Matrix3 m;
	m.setScale(x, y, z);
	*this = *this * m;
}

void Matrix3::scale(const Vector3 & vec)
{
	Matrix3 m;
	m.setScale(vec.x, vec.y, vec.z);
	*this = *this * m;
}

Matrix3 Matrix3::inverse(Matrix3 & mat)									//Static matrix inverse
{
	double determinant =	mat.data[0][0] * (mat.data[1][1] * mat.data[2][2] - mat.data[2][1] * mat.data[1][2]) -
							mat.data[0][1] * (mat.data[1][0] * mat.data[2][2] - mat.data[1][2] * mat.data[2][0]) +
							mat.data[0][2] * (mat.data[1][0] * mat.data[2][1] - mat.data[1][1] * mat.data[2][0]);

	double invDeterminant = 1 / determinant;

	Matrix3 inverse;

	inverse.data[0][0] = (mat.data[1][1] * mat.data[2][2] - mat.data[2][1] * mat.data[1][2]) * invDeterminant;
	inverse.data[0][1] = (mat.data[0][2] * mat.data[2][1] - mat.data[0][1] * mat.data[2][2]) * invDeterminant;
	inverse.data[0][2] = (mat.data[0][1] * mat.data[1][2] - mat.data[0][2] * mat.data[1][1]) * invDeterminant;

	inverse.data[1][0] = (mat.data[1][2] * mat.data[2][0] - mat.data[1][0] * mat.data[2][2]) * invDeterminant;
	inverse.data[1][1] = (mat.data[0][0] * mat.data[2][2] - mat.data[0][2] * mat.data[2][0]) * invDeterminant;
	inverse.data[1][2] = (mat.data[1][0] * mat.data[0][2] - mat.data[0][0] * mat.data[1][2]) * invDeterminant;

	inverse.data[2][0] = (mat.data[1][0] * mat.data[2][1] - mat.data[2][0] * mat.data[1][1]) * invDeterminant;
	inverse.data[2][1] = (mat.data[2][0] * mat.data[0][1] - mat.data[0][0] * mat.data[2][1]) * invDeterminant;
	inverse.data[2][2] = (mat.data[0][0] * mat.data[1][1] - mat.data[1][0] * mat.data[0][1]) * invDeterminant;

	return inverse;
}

void Matrix3::inverse()													//Self inverse
{
	double determinant =	data[0][0] * (data[1][1] * data[2][2] - data[2][1] * data[1][2]) -
							data[0][1] * (data[1][0] * data[2][2] - data[1][2] * data[2][0]) +
							data[0][2] * (data[1][0] * data[2][1] - data[1][1] * data[2][0]);

	double invDeterminant = 1 / determinant;

	Matrix3 inverse;

	inverse.data[0][0] = (data[1][1] * data[2][2] - data[2][1] * data[1][2]) * invDeterminant;
	inverse.data[0][1] = (data[0][2] * data[2][1] - data[0][1] * data[2][2]) * invDeterminant;
	inverse.data[0][2] = (data[0][1] * data[1][2] - data[0][2] * data[1][1]) * invDeterminant;

	inverse.data[1][0] = (data[1][2] * data[2][0] - data[1][0] * data[2][2]) * invDeterminant;
	inverse.data[1][1] = (data[0][0] * data[2][2] - data[0][2] * data[2][0]) * invDeterminant;
	inverse.data[1][2] = (data[1][0] * data[0][2] - data[0][0] * data[1][2]) * invDeterminant;

	inverse.data[2][0] = (data[1][0] * data[2][1] - data[2][0] * data[1][1]) * invDeterminant;
	inverse.data[2][1] = (data[2][0] * data[0][1] - data[0][0] * data[2][1]) * invDeterminant;
	inverse.data[2][2] = (data[0][0] * data[1][1] - data[1][0] * data[0][1]) * invDeterminant;

	*this = inverse;
}

Matrix3 Matrix3::inverseCpy() const										//Returns inverted copy of this matrix
{
	double determinant = data[0][0] * (data[1][1] * data[2][2] - data[2][1] * data[1][2]) -
		data[0][1] * (data[1][0] * data[2][2] - data[1][2] * data[2][0]) +
		data[0][2] * (data[1][0] * data[2][1] - data[1][1] * data[2][0]);

	double invDeterminant = 1 / determinant;

	Matrix3 inverse;

	inverse.data[0][0] = (data[1][1] * data[2][2] - data[2][1] * data[1][2]) * invDeterminant;
	inverse.data[0][1] = (data[0][2] * data[2][1] - data[0][1] * data[2][2]) * invDeterminant;
	inverse.data[0][2] = (data[0][1] * data[1][2] - data[0][2] * data[1][1]) * invDeterminant;

	inverse.data[1][0] = (data[1][2] * data[2][0] - data[1][0] * data[2][2]) * invDeterminant;
	inverse.data[1][1] = (data[0][0] * data[2][2] - data[0][2] * data[2][0]) * invDeterminant;
	inverse.data[1][2] = (data[1][0] * data[0][2] - data[0][0] * data[1][2]) * invDeterminant;

	inverse.data[2][0] = (data[1][0] * data[2][1] - data[2][0] * data[1][1]) * invDeterminant;
	inverse.data[2][1] = (data[2][0] * data[0][1] - data[0][0] * data[2][1]) * invDeterminant;
	inverse.data[2][2] = (data[0][0] * data[1][1] - data[1][0] * data[0][1]) * invDeterminant;

	return inverse;
}

Matrix3::operator float*()						//Mutator float cast
{
	return &data[0][0];
}

Matrix3::operator const float*() const			//Inspector float cast
{
	return &data[0][0];
}

}