//pkr Math Library
//Author: Tony Le
//Version: 1.0

#pragma once
#include "Vector3.h"

namespace pkr {

class Vector2;

class Vector4
{
public:
	union
	{
		//Homogenous
		struct {
			float x, y, z, w;
		};

		//Colour
		struct {
			float r, g, b, alpha;
		};

		//Array
		float data[4];
	};
	static const float DEF_TOLERANCE;

	Vector4();															//Default
	Vector4(float x, float y, float z, float w = 1);					//Initialiser (automatic 3D or 4D)
	Vector4(const Vector3& other);										//3D Copy Constructor
	Vector4(const Vector4& other);										//4D Copy Constructor
	~Vector4();															//Destructor

	//Operators
	Vector4		operator - () const;									//UNARY minus
	Vector4		operator + (const Vector4 &other) const;				//Point/Vector to Vector add (point translated by a vector)
	Vector4		operator - (const Vector4 &other) const;				//Point/Vector to Vector subtract (point translated by a vector)
	
	Vector4		operator * (float scalar) const;						//POST Scalar multiply (vector scale)
	Vector4		operator / (float scalar) const;						//POST Scalar divide (vector scale)
	friend Vector4 operator * (float scalar, const Vector4 &other);		//PRE Scalar multiply (vector scale)

	Vector4&	operator += (const Vector4 &other);						//Point/Vector to Vector add assign
	Vector4&	operator -= (const Vector4 &other);						//Point/Vector to Vector subtract assign
	Vector4&	operator *= (float scalar);								//Scalar multiply assign
	Vector4&	operator /= (float scalar);								//Scalar divide assign
	
	Vector4&	operator = (const Vector3 &other);						//Assignment by Vector3
	Vector4&	operator = (const Vector4 &other);						//Assignment by Vector4
	bool		operator == (const Vector4 &other);						//Equality check
	bool		operator != (const Vector4 &other);						//Inequality check
	bool		equal(const Vector4 &other, float tolerance = DEF_TOLERANCE);			//Equality check with tolerance
	bool		notEqual(const Vector4 &other, float tolerance = DEF_TOLERANCE);		//Inequality check with tolerance

	//Subscript
	float		operator [] (int index) const;							//Inspector; Returns value at index
	float&		operator [] (int index);								//Mutator; Returns address of index for assignment

	//Casts
	operator	float*();												//Mutator float pointer cast
	operator	const float*() const;									//Inspector float pointer cast

	//Dot
	static float	dot(const Vector4 &a, const Vector4 &b);				//Dot product of input vectors
	float			dot(const Vector4 &other) const;						//Dot product

	//Cross
	static Vector4	cross(const Vector4 &a, const Vector4 &b);				//Cross product of input vectors
	Vector4			cross(const Vector4 &other) const;						//Cross product

	//Angle between
	static float	angleBetween(const Vector4 &a, const Vector4 &b);		//Angle between two input vectors in degrees
	float			angleBetween(const Vector4 &other) const;				//Angle between another vector in degrees

	//Magnitude
	static float	magnitude(const Vector4 &vec);							//Magnitude of input vector
	float			magnitude();											//Magnitude of vector
	float			magnitudeSqr() const;									//Magnitude squared for efficient comparison
	void			setMagnitude(float mag);							//Sets magnitude of vector

	//Distance
	static float	distance(const Vector4 &a, const Vector4 &b);			//Distance between two input vectors
	float			distance(const Vector4 &other) const;					//Distance between another vector
	float			distanceSqr(const Vector4 &vec) const;					//Distance squared for efficient comparison

	//Normalise
	static Vector4	normalise(const Vector4 &vec);							//Normalised copy of input vector
	void			normalise();											//Normalise this vector
	Vector4			normaliseCpy() const;									//Normalised copy of this vector

	//Absolute
	static Vector4	absolute(const Vector4 &vec);							//Absolute copy of input vector
	void			absolute();												//Make this vector absolute
	Vector4			absoluteCpy() const;									//Absolute copy of this vector
};

}