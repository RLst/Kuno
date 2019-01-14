//pkr Math Library
//Author: Tony Le
//Version: 1.0

#pragma once
#include "Vector2.h"

namespace pkr {

class Vector2;

struct Matrix2
{
public:
	union {
		//Standard
		struct {
			Vector2 xAxis;
			Vector2 yAxis;	
		};
		//Arrays
		Vector2 axis[2];
		float data[2][2];
	};
	static const Matrix2 identity;
	static const float DEF_TOLERANCE;

	Matrix2();																//Default
	Matrix2(float Xx, float Xy,												//Initialise
			float Yx, float Yy);				
	Matrix2(Vector2 &X, Vector2 &Y);										//Initialise by vectors
	Matrix2(const Matrix2& other);											//Copy
	~Matrix2();																//Destructor

	//Subscript
	Vector2&		operator [] (int index);								//Mutator
	const Vector2&	operator [] (int index) const;							//Inspector

	//Equality
	Matrix2&		operator = (const Matrix2 &other);						//Assignment
	bool			operator == (const Matrix2 &other) const;				//Equality check
	bool			operator != (const Matrix2 &other) const;				//Inequality check

	//Tolerance checks
	bool			equal(const Matrix2 &other, float tolerance = DEF_TOLERANCE) const;		//Equality check with tolerance
	bool			notEqual(const Matrix2 &other, float tolerance = DEF_TOLERANCE) const;	//Inequality check with tolerance

	//Add and subtract
	Matrix2			operator + (const Matrix2 &other) const;				//Addition
	Matrix2			operator - (const Matrix2 &other) const;				//Subtraction
	Matrix2&		operator += (const Matrix2 &other);						//Addition assign
	Matrix2&		operator -= (const Matrix2 &other);						//Subtract assign

	//Scalar operations
	Matrix2			operator * (float scalar) const;						//POST Scalar multiply 
	Matrix2			operator / (float scalar) const;						//POST Scalar division
	friend Matrix2	operator * (float scalar, const Matrix2 &other);		//PRE scalar multiply
	Matrix2&		operator *= (float scalar);								//Scalar multiply assign
	Matrix2&		operator /= (float scalar);								//Scalar division assign

	//Matrix Multiply
	Matrix2			operator * (const Matrix2 &other) const;				//Multiply with non-member matrix
	Vector2			operator * (const Vector2 &vec) const;					//Multiply with non-member vector

	//Transpose
	Matrix2			transposed() const;										//Returns a transposed copy

	//Rotation
	static Matrix2	createRotate(float radians);							//Create, rotate and return non-member matrices
	void			setRotate(float radians);								//Set rotates (Z)
	void			rotate(float radians);									//Rotate (Z)

	//Scaling
	static Matrix2	createScale(float x, float y);							//Create, scale and return non-member matrices
	static Matrix2	createScale(const Vector2 &vec);
	void			setScale(float x, float y);								//Set scale by axis
	void			setScale(const Vector2 &vec);							//Set scale by vector
	void			scale(float x, float y);								//Scale by axis
	void			scale(const Vector2 &vec);								//Scale by vector

	//Cast
	operator		float*();												//Mutable float pointer cast
	operator		const float*() const;									//Inspector float pointer cast
};

}