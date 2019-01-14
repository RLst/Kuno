//pkr Math Library
//Author: Tony Le
//Version: 1.0

#pragma once
#include "Vector3.h"

namespace pkr {

class Vector2;
class Vector4;

class Matrix3
{
public:
	union {
		//Standard and Homogeneous
		struct {
			Vector3 xAxis;
			Vector3 yAxis;
			union {
				Vector3 zAxis;
				Vector3 translation;
			};
		};

		//Arrays
		Vector3 axis[3];
		float data[3][3];														
	};
	static const Matrix3 identity;
	static const float DEF_TOLERANCE;

	Matrix3();																//Default
	Matrix3(float Xx, float Xy, float Xz,									//Initialise
			float Yx, float Yy, float Yz,
			float Zx, float Zy, float Zz);						
	Matrix3(Vector3 &X, Vector3 &Y, Vector3 &Z);							//Initialise by vectors
	Matrix3(const Matrix3& other);											//Copy
	~Matrix3();																//Destructor

	//Subscript
	Vector3&		operator [] (int index);								//Mutator
	const Vector3&	operator [] (int index) const;							//Inspector

	//Equality
	Matrix3&		operator = (const Matrix3 &other);						//Assignment
	bool			operator == (const Matrix3 &other) const;				//Equality check
	bool			operator != (const Matrix3 &other) const;				//Inequality check

	//Tolerance checks
	bool			equal(const Matrix3 &other, float tolerance = DEF_TOLERANCE) const;		//Equality check with tolerance
	bool			notEqual(const Matrix3 &other, float tolerance = DEF_TOLERANCE) const;	//Inequality check with tolerance

	//Add and subtract
	Matrix3			operator + (const Matrix3 &other) const;				//Addition
	Matrix3			operator - (const Matrix3 &other) const;				//Subtraction
	Matrix3&		operator += (const Matrix3 &other);						//Addition assign
	Matrix3&		operator -= (const Matrix3 &other);						//Subtract assign

	//Scalar operations
	Matrix3			operator * (float scalar) const;						//POST Scalar multiply 
	Matrix3			operator / (float scalar) const;						//POST Scalar division
	friend Matrix3	operator * (float scalar, const Matrix3 &other);		//PRE Scalar multiply
	Matrix3&		operator *= (float scalar);								//Scalar multiply assign
	Matrix3&		operator /= (float scalar);								//Scalar division assign

	//Matrix Multiply
	Matrix3			operator * (const Matrix3 &other) const;				//Multiply with non-member matrix
	Vector3			operator * (const Vector3 &vec) const;					//Multiply with non-member vector

	//Transpose
	Matrix3			transposed() const;										//Returns a transposed copy

	//2D Translate
	static Matrix3	createTranslate(float x, float y);						//Create and translate by points
	static Matrix3	createTranslate(const Vector3 &vec);					//Create and translate by vector
	void			setTranslate(float x, float y);							//Translate THIS
	void			translate(float x, float y);							//Applies translation to this
	void			translate(const Vector3 &vec);							//Applies translation to this

	//Rotation
	static Matrix3	createRotateX(float radians);							//Create, rotate and return non-member matrices
	static Matrix3	createRotateY(float radians);
	static Matrix3	createRotateZ(float radians);							//FOR Homogenenous 2D!!
	void			setRotateX(float radians);								//Set rotates
	void			setRotateY(float radians);
	void			setRotateZ(float radians);
	void			rotateX(float radians);									//Rotate
	void			rotateY(float radians);
	void			rotateZ(float radians);
	void			setEuler(float pitch, float yaw, float roll);			//Set euler

	//Scaling
	static Matrix3	createScale(float x, float y, float z);					//Create, scale and return non-member matrix
	static Matrix3	createScale(const Vector3 &vec);						
	void			setScale(float x, float y, float z);					//Scale THIS
	void			scale(float x, float y, float z);						//Scale by axis
	void			scale(const Vector3 &vec);								//Scale by vector

	//Inverse
	static Matrix3	inverse(Matrix3 & mat);									//Inverse input matrix
	void			inverse();												//Self-inverse
	Matrix3			inverseCpy() const;										//Return inverse copy

	//Cast
	operator		float*();												//Mutable float pointer cast
	operator		const float*() const;									//Inspector float pointer cast
};

}
