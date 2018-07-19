//pkr Math Library
//Author: Tony Le
//Version: 1.0


#include "Matrix4.h"
#include <cmath>

namespace pkr {

const float Matrix4::DEF_TOLERANCE = 0.00001f;
const Matrix4 Matrix4::identity = Matrix4(	1, 0, 0, 0,
											0, 1, 0, 0,
											0, 0, 1, 0,
											0, 0, 0, 1);

Matrix4::Matrix4()																		//Default
{
	//Initialise as an identity matrix
	*this = identity;
	////Clear the matrix
	//for (int r = 0; r < 4; ++r)
	//	for (int c = 0; c < 4; ++c)
	//		data[r][c] = 0;
}

Matrix4::Matrix4(float Xx, float Xy, float Xz, float Xw,								//Init
				 float Yx, float Yy, float Yz, float Yw, 
				 float Zx, float Zy, float Zz, float Zw, 
				 float Tx, float Ty, float Tz, float Tw)
{
	xAxis.x = Xx; xAxis.y = Xy; xAxis.z = Xz; xAxis.w = Xw;
	yAxis.x = Yx; yAxis.y = Yy; yAxis.z = Yz; yAxis.w = Yw;
	zAxis.x = Zx; zAxis.y = Zy; zAxis.z = Zz; zAxis.w = Zw;
	translation.x = Tx; translation.y = Ty; translation.z = Tz; translation.w = Tw;
}

Matrix4::Matrix4(Vector3 & X, Vector3 & Y, Vector3 & Z)									//Init by 3D vectors
{
	xAxis = X;
	yAxis = Y;
	zAxis = Z;
	translation = { 0, 0, 0, 1 };
}

Matrix4::Matrix4(Vector4 & X, Vector4 & Y, Vector4 & Z, Vector4 & T)					//Init by 4D vectors
{
	xAxis = X;
	yAxis = Y;
	zAxis = Z;
	translation = T;
}

Matrix4::Matrix4(const Matrix4 & other)													//Copy
{
	//Copy other to this
	for (int r = 0; r < 4; ++r)
		for (int c = 0; c < 4; ++c)
			data[r][c] = other.data[r][c];
}

Matrix4::~Matrix4()																		//Destructor
{}

Vector4 & Matrix4::operator[](int index)
{
	return axis[index];
}

const Vector4 & Matrix4::operator[](int index) const
{
	return axis[index];
}

Matrix4 & Matrix4::operator=(const Matrix4 & other)
{
	for (int r = 0; r < 4; ++r)
		for (int c = 0; c < 4; ++c)
			data[r][c] = other.data[r][c];
	return *this;
}

bool Matrix4::operator==(const Matrix4 & other) const
{
	for (int r = 0; r < 4; ++r)
		for (int c = 0; c < 4; ++c)
			if (data[r][c] != other.data[r][c])
				return false;	//Something is NOT EQUAL so return false
	return true;	//All EQUAL
}

bool Matrix4::operator!=(const Matrix4 & other) const
{
	for (int r = 0; r < 4; ++r)
		for (int c = 0; c < 4; ++c)
			if (data[r][c] == other.data[r][c])
				return false;	//Something is NOT NOT EQUAL so return false
	return true;	//All NOT EQUAL
}

bool Matrix4::equal(const Matrix4 & other, float tolerance) const
{
	//If any of one the element comparisons fails, then return false
	//Otherwise all elements are all EQUAL within the specified tolerance
	for (int r = 0; r < 4; ++r)
		for (int c = 0; c < 4; ++c) {
			if (abs(data[r][c] - other.data[r][c] >= tolerance))
				return false;
		}
	return true;
}

bool Matrix4::notEqual(const Matrix4 & other, float tolerance) const
{
	//If any of one the element comparisons fails, then return false
	//Otherwise all elements are all NOT EQUAL within the specified tolerance
	for (int r = 0; r < 4; ++r)
		for (int c = 0; c < 4; ++c) {
			if (abs(data[r][c] - other.data[r][c]) < tolerance)
				return false;
		}
	return true;
}

Matrix4 Matrix4::operator+(const Matrix4 & other) const
{
	Matrix4 result;		//Creates a seperate matrix
	for (int r = 0; r < 4; ++r)
		for (int c = 0; c < 4; ++c)
			result.data[r][c] = data[r][c] + other.data[r][c];		//Perform operation between this and other, and assign onto resultant matrix
	return result;		//Return resultant matrix
}

Matrix4 Matrix4::operator-(const Matrix4 & other) const
{
	Matrix4 result;		//Creates a seperate matrix
	for (int r = 0; r < 4; ++r)
		for (int c = 0; c < 4; ++c)
			result.data[r][c] = data[r][c] - other.data[r][c];		//Perform operation between this and other, and assign onto resultant matrix
	return result;		//Return resultant matrix
}

Matrix4 & Matrix4::operator+=(const Matrix4 & other)
{
	//Perform operation between this and other and return this
	for (int r = 0; r < 4; ++r) {
		for (int c = 0; c < 4; ++c) {
			data[r][c] += other.data[r][c];
		}
	}
	return *this;
}

Matrix4 & Matrix4::operator-=(const Matrix4 & other)
{
	//Perform operation between this and other and return this
	for (int r = 0; r < 4; ++r) {
		for (int c = 0; c < 4; ++c) {
			data[r][c] -= other.data[r][c];
		}
	}
	return *this;
}

Matrix4 Matrix4::operator*(float scalar) const
{
	//Perform scalar operation on this, assign to new matrix and return
	Matrix4 result;
	for (int r = 0; r < 4; ++r)
		for (int c = 0; c < 4; ++c)
			result.data[r][c] = data[r][c] * scalar;
	return result;
}

Matrix4 Matrix4::operator/(float scalar) const
{
	//Perform scalar operation on this, assign to new matrix and return
	Matrix4 result;
	for (int r = 0; r < 4; ++r)
		for (int c = 0; c < 4; ++c)
			result.data[r][c] = data[r][c] / scalar;
	return result;
}

Matrix4 operator*(float scalar, const Matrix4 & other)
{
	//Perform scalar operation on other, assign to new matrix and return
	Matrix4 result;
	for (int r = 0; r < 4; ++r)
		for (int c = 0; c < 4; ++c)
			result.data[r][c] = other.data[r][c] * scalar;
	return result;
}

Matrix4 & Matrix4::operator*=(float scalar)
{
	//Perform scalar operation on this and return this
	for (int r = 0; r < 4; ++r) {
		for (int c = 0; c < 4; ++c) {
			data[r][c] *= scalar;
		}
	}
	return *this;
}

Matrix4 & Matrix4::operator/=(float scalar)
{
	//Perform scalar operation on this and return this
	for (int r = 0; r < 4; ++r) {
		for (int c = 0; c < 4; ++c) {
			data[r][c] /= scalar;
		}
	}
	return *this;
}

Matrix4 Matrix4::operator*(const Matrix4 & other) const
{
	//Multiply this with non-member matrix and return resultant
	Matrix4 result;
	for (int r = 0; r < 4; ++r) {
		for (int c = 0; c < 4; ++c) {
			result.data[c][r] = data[0][r] * other.data[c][0] +
								data[1][r] * other.data[c][1] +
								data[2][r] * other.data[c][2] +
								data[3][r] * other.data[c][3];
		}
	}
	return result;
}

Vector4 Matrix4::operator*(const Vector4 & vec) const
{
	//Multiply this with non-member vector and return resultant
	Vector4 result;
	for (int r = 0; r < 4; ++r) {
		result[r] = data[0][r] * vec[0] +
					data[1][r] * vec[1] +
					data[2][r] * vec[2] + 
					data[3][r] * vec[3];
	}
	return result;
}

Matrix4 Matrix4::transposed() const
{
	//Flip row and column
	Matrix4 result;
	for (int r = 0; r < 4; ++r) {
		for (int c = 0; r < 4; ++c) {
			result.data[r][c] = data[c][r];
		}
	}
	return result;
}

Matrix4 Matrix4::createTranslate(float x, float y, float z)
{
	Matrix4 m;
	m.setTranslate(x, y, z);
	return m;
}

Matrix4 Matrix4::createTranslate(const Vector4 & vec)
{
	Matrix4 m;
	m.setTranslate(vec.x, vec.y, vec.z);
	return m;
}

void Matrix4::setTranslate(float x, float y, float z)
{
	//Set translation axis
	translation = { x, y, z, 0 };
}

void Matrix4::translate(float x, float y, float z)
{
	//Apply vector offset
	translation += { x, y, z, 0 };
}

void Matrix4::translate(Vector4 & vec)
{
	//Apply vector offset
	translation += vec;
}

Matrix4 Matrix4::createRotateX(float radians)
{
	Matrix4 m;
	m.setRotateX(radians);
	return m;
}

Matrix4 Matrix4::createRotateY(float radians)
{
	Matrix4 m;
	m.setRotateY(radians);
	return m;
}

Matrix4 Matrix4::createRotateZ(float radians)
{
	Matrix4 m;
	m.setRotateZ(radians);
	return m;
}

void Matrix4::setRotateX(float radians)
{
	//Leave X axis and elements unchanged
	xAxis = { 1, 0, 0, 0 };
	yAxis = { 0 , cosf(radians), sinf(radians), 0 };
	zAxis = { 0 , -sinf(radians), cosf(radians), 0 };
	translation = { 0, 0, 0, 1 };
}

void Matrix4::setRotateY(float radians)
{
	//Leave Y axis and elements unchanged
	xAxis = { cosf(radians), 0, -sinf(radians), 0 };
	yAxis = { 0, 1, 0, 0 };
	zAxis = { sinf(radians), 0, cosf(radians), 0 };
	translation = { 0, 0, 0, 1 };
}

void Matrix4::setRotateZ(float radians)
{
	//Leave Z axis and elements unchanged
	xAxis = { cosf(radians), sinf(radians), 0, 0 };
	yAxis = { -sinf(radians), cosf(radians), 0, 0 };
	zAxis = { 0, 0, 1, 0 };
	translation = { 0, 0, 0, 1 };
}

void Matrix4::rotateX(float radians)			//Non-member rotates
{
	Matrix4 m;
	m.setRotateX(radians);
	*this = *this * m;
}

void Matrix4::rotateY(float radians)
{
	Matrix4 m;
	m.setRotateY(radians);
	*this = *this * m;
}

void Matrix4::rotateZ(float radians)
{
	Matrix4 m;
	m.setRotateZ(radians);
	*this = *this * m;
}

void Matrix4::setEuler(float pitch, float yaw, float roll)
{
	Matrix4 x, y, z;
	y.setRotateX(pitch);
	y.setRotateY(yaw);
	z.setRotateZ(roll);
	//Combine rotations in a specific order
	*this = z * y * x;
}

Matrix4 Matrix4::createScale(float x, float y, float z)
{
	Matrix4 m;
	m.setScale(x, y, z);
	return m;
}

Matrix4 Matrix4::createScale(const Vector4 & vec)
{
	Matrix4 m;
	m.setScale(vec.x, vec.y, vec.z);
	return m;
}

void Matrix4::setScale(float x, float y, float z)
{
	//Set scale of each axis
	xAxis = { x, 0, 0, 0 };
	yAxis = { 0, y, 0, 0 };
	zAxis = { 0, 0, z, 0 };
	translation = { 0, 0, 0, 1 };
}

void Matrix4::scale(float x, float y, float z)
{
	Matrix4 m;
	m.setScale(x, y, z);
	*this = *this * m;
}

void Matrix4::scale(const Vector4 & vec)
{
	Matrix4 m;
	m.setScale(vec.x, vec.y, vec.z);
	*this = *this * m;
}


Matrix4::operator float*()						//Mutator float casts
{
	return &data[0][0];
}

Matrix4::operator const float*() const			//Inspector float casts
{
	return &data[0][0];
}

}