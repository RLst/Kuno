//pkr Math Library
//Author: Tony Le
//Version: 1.0

#pragma once
#include "Vector3.h"
#include "Vector4.h"

namespace pkr {

class Matrix4
{
public:
	union {
		//Homogeneous
		struct {
			Vector4 xAxis;
			Vector4 yAxis;
			Vector4 zAxis;
			Vector4 translation;
		};

		//Arrays
		Vector4 axis[4];
		float data[4][4];
	};
	static const Matrix4 identity;
	static const float DEF_TOLERANCE;

	Matrix4();																//Default
	Matrix4(float Xx, float Xy, float Xz, float Xw,							//Initialise
			float Yx, float Yy, float Yz, float Yw,
			float Zx, float Zy, float Zz, float Zw,
			float Tx, float Ty, float Tz, float Tw);
	Matrix4(Vector3 &X, Vector3 &Y, Vector3 &Z);							//Initialise by 3D vectors
	Matrix4(Vector4 &X, Vector4 &Y, Vector4 &Z, Vector4 &T);				//Initialise by 4D vectors
	Matrix4(const Matrix4& other);											//Copy
	~Matrix4();																//Destructor

	//Subscript
	Vector4&		operator [] (int index);								//Mutator
	const Vector4&	operator [] (int index) const;							//Inspector

	//Equality
	Matrix4&		operator = (const Matrix4 &other);						//Assignment
	bool			operator == (const Matrix4 &other) const;				//Equality check
	bool			operator != (const Matrix4 &other) const;				//Inequality check

	//Tolerance checks
	bool			equal(const Matrix4 &other, float tolerance = DEF_TOLERANCE) const;		//Equality check with tolerance
	bool			notEqual(const Matrix4 &other, float tolerance = DEF_TOLERANCE) const;	//Inequality check with tolerance

	//Add and subtract
	Matrix4			operator + (const Matrix4 &other) const;				//Addition
	Matrix4			operator - (const Matrix4 &other) const;				//Subtraction
	Matrix4&		operator += (const Matrix4 &other);						//Addition assign
	Matrix4&		operator -= (const Matrix4 &other);						//Subtract assign

	//Scalar operations
	Matrix4			operator * (float scalar) const;						//POST Scalar multiply 
	Matrix4			operator / (float scalar) const;						//POST Scalar division
	friend Matrix4	operator * (float scalar, const Matrix4 &other);		//PRE Scalar multiply
	Matrix4&		operator *= (float scalar);								//Scalar multiply assign
	Matrix4&		operator /= (float scalar);								//Scalar division assign

	//Matrix Multiply
	Matrix4			operator * (const Matrix4 &other) const;				//Multiply with non-member matrix
	Vector4			operator * (const Vector4 &vec) const;					//Multiply with non-member vector

	//Transpose
	Matrix4			transposed() const;										//Returns a transposed copy

	//3D Translate
	static Matrix4	createTranslate(float x, float y, float z);				//Create and translate by points
	static Matrix4	createTranslate(const Vector4 &vec);					//Create and translate by vector
	void			setTranslate(float x, float y, float z);				//Translate THIS
	void			translate(float x, float y, float z);					//Translate by axis
	void			translate(Vector4 &vec);								//Translate by vector 4

	//Rotation
	static Matrix4	createRotateX(float radians);							//Create, rotate and return non-member matrices
	static Matrix4	createRotateY(float radians);
	static Matrix4	createRotateZ(float radians);
	void			setRotateX(float radians);								//Set rotates
	void			setRotateY(float radians);
	void			setRotateZ(float radians);
	void			rotateX(float radians);									//Rotate
	void			rotateY(float radians);
	void			rotateZ(float radians);
	void			setEuler(float pitch, float yaw, float roll);			//Set euler

	//Scaling
	static Matrix4	createScale(float x, float y, float z);					//Create, scale and return non-member matrices
	static Matrix4	createScale(const Vector4 &vec);
	void			setScale(float x, float y, float z);					//Set scaled by axis
	void			scale(float x, float y, float z);						//Scale by axis
	void			scale(const Vector4 &vec);								//Scale by vector

	//Cast
	operator		float*();												//Mutable float pointer cast
	operator		const float*() const;									//Inspector float pointer cast
};

}
