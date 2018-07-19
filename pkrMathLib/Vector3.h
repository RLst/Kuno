//pkr Math Library
//Author: Tony Le
//Version: 1.0

#pragma once

namespace pkr {

class Vector2;
class Vector4;

class Vector3
{
	static const float DEFAULT_TOLERANCE;	//Have to set the value in the cpp file
public:
	union
	{
		//Standard
		struct {
			float x, y;
			union {	//Homogeneous
				float z;
				float w;
			};
		};

		//Rotation
		struct {
			float xa, ya, za;
		};

		//Colour
		struct {
			float r, g, b;
		};

		//Array
		float data[3];
	};
	static const float DEF_TOLERANCE;

	Vector3();																//Default
	Vector3(float x, float y, float z);										//Initialiser
	Vector3(const Vector2 &other);											//2D Copy Constructor
	Vector3(const Vector3 &other);											//3D Copy Constructor
	Vector3(const Vector4 &other);											//4D Copy Constructor
	~Vector3();																//Destructor

	//Operators
	Vector3			operator - () const;									//UNARY minus
	Vector3			operator + (const Vector3 &other) const;				//Point/Vector to Vector add (point translated by a vector)
	Vector3			operator - (const Vector3 &other) const;				//Point/Vector to Vector subtract (point translated by a vector)
	
	Vector3			operator * (float scalar) const;						//POST Scalar multiply (vector scale)
	Vector3			operator / (float scalar) const;						//POST Scalar divide (vector scale)
	friend Vector3	operator * (float scalar, const Vector3 &other);		//PRE Scalar multiply (vector scale)

	Vector3&		operator += (const Vector3 &other);						//Point/Vector to Vector add assign
	Vector3&		operator -= (const Vector3 &other);						//Point/Vector to Vector subtract assign
	Vector3&		operator *= (float scalar);								//Scalar multiply assign
	Vector3&		operator /= (float scalar);								//Scalar divide assign

	Vector3&		operator = (const Vector3 &other);						//Assignment
	bool			operator == (const Vector3 &other);						//Equality check
	bool			operator != (const Vector3 &other);						//Inequality check
	bool			equal(const Vector3 &other, float tolerance = DEF_TOLERANCE);			//Equality check with tolerance
	bool			notEqual(const Vector3 &other, float tolerance = DEF_TOLERANCE);		//Inequality check with tolerance

	//Subscript
	float			operator [] (int index) const;							//Inspector; Returns value at index
	float&			operator [] (int index);								//Mutator; Returns address of index for assignment

	//Casts
	operator		float*();												//Mutator float pointer cast
	operator		const float*() const;									//Inspector float pointer cast

	//Dot
	static float	dot(const Vector3 &a, const Vector3 &b);				//Dot product of input vectors
	float			dot(const Vector3 &other) const;						//Dot product

	//Cross
	static Vector3	cross(const Vector3 &a, const Vector3 &b);				//Cross product of input vectors
	Vector3			cross(const Vector3 &other) const;						//Cross product

	//Angle between
	static float	angleBetween(const Vector3 &a, const Vector3 &b);		//Angle between two input vectors in degrees
	float			angleBetween(const Vector3 &other) const;				//Angle between another vector in degrees

	//Magnitude
	static float	magnitude(const Vector3 &vec);							//Magnitude of input vector
	float			magnitude();											//Magnitude of vector
	float			magnitudeSqr() const;									//Magnitude squared for efficient comparison
	void			setMagnitude(float mag);							//Sets magnitude of vector
	
	//Distance
	static float	distance(const Vector3 &a, const Vector3 &b);			//Distance between two input vectors
	float			distance(const Vector3 &other) const;					//Distance between another vector
	float			distanceSqr(const Vector3 &vec) const;					//Distance squared for efficient comparison

	//Normalise
	static Vector3	normalise(const Vector3 &vec);							//Normalised copy of input vector
	void			normalise();											//Normalise this vector
	Vector3			normaliseCpy() const;									//Normalised copy of this vector

	//Absolute
	static Vector3	absolute(const Vector3 &vec);							//Absolute copy of input vector
	void			absolute();												//Make this vector absolute
	Vector3			absoluteCpy() const;									//Absolute copy of this vector
};

}