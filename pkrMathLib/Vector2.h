//pkr Math Library
//Author: Tony Le
//Version: 1.0

#pragma once

namespace pkr {

class Vector3;

class Vector2
{
	static const float DEFAULT_TOLERANCE;
public:
	union
	{
		//Standard
		struct {
			float x, y;
		};

		//Angle and magnitude
		struct {
			float a, M;
		};

		//Rotation
		struct {
			float xa, ya;
		};

		//Array
		float data[2];
	};
	static const float DEF_TOLERANCE;

	Vector2();															//Default
	Vector2(float x, float y);											//Initialiser
	Vector2(const Vector2& other);										//Copy
	Vector2(const Vector3& other);										//3D Copy
	~Vector2();															//Destructor

	//Operators
	Vector2			operator - () const;									//UNARY minus
	Vector2			operator + (const Vector2 &other) const;				//Point/Vector to Vector add (point translated by a vector)
	Vector2			operator - (const Vector2 &other) const;				//Point/Vector to Vector subtract (point translated by a vector)
	
	Vector2			operator * (float scalar) const;					 	//POST Scalar multiply (vector scale)
	Vector2			operator / (float scalar) const;					 	//POST Scalar divide (vector scale)
	friend Vector2	operator * (float scalar, const Vector2 &other);		//PRE Scalar multiply (vector scale)

	Vector2&		operator += (const Vector2 &other);						//Point/Vector to Vector add assign
	Vector2&		operator -= (const Vector2 &other);						//Point/Vector to Vector subtract assign
	Vector2&		operator *= (float scalar);								//Scalar multiply assign
	Vector2&		operator /= (float scalar);								//Scalar divide assign
	
	Vector2&		operator = (const Vector2 &other);						//Assignment
	bool			operator == (const Vector2 &other);						//Equality check
	bool			operator != (const Vector2 &other);						//Inequality check
	bool			equal(const Vector2 &other, float tolerance = DEF_TOLERANCE);			//Equality check with tolerance
	bool			notEqual(const Vector2 &other, float tolerance = DEF_TOLERANCE);		//Inequality check with tolerance
	
	//Subscript	
	float			operator [] (int index) const;							//Inspector; Returns value at index
	float&			operator [] (int index);								//Mutator; Returns address of index for assignment
	
	//Casts	
	operator		float*();												//Mutator float pointer cast
	operator		const float*() const;									//Inspector float pointer cast

	//Dot
	static float	dot(const Vector2 &a, const Vector2 &b);				//Dot product with non-members
	float			dot(const Vector2 &other) const;						//Dot product
																		
	//Perpendiculars
	Vector2			getPerpendRH() const;									//2D Cross product equivalent
	Vector2			getPerpendLH() const;									//2D Cross product equivalent

	//Angle between
	static float	angleBetween(const Vector2 &a, const Vector2 &b);		//Angle between two input vectors
	float			angleBetween(const Vector2 &other) const;				//Angle between another vector

	//Magnitude
	static float	magnitude(const Vector2 &vec);							//Magnitude of input vector
	float			magnitude();											//Magnitude of vector
	float			magnitudeSqr() const;									//Magnitude squared for efficient comparison
	void			setMagnitude(float mag);							//Sets magnitude of vector

	//Distance	
	static float	distance(const Vector2 &A, const Vector2 &B);			//Distance between two input vectors
	static float	distanceSqr(const Vector2 &A, const Vector2 &B);		//Distance squared between to input vectors (efficient)	
	float			distance(const Vector2 &other) const;					//Distance between another vector
	float			distanceSqr(const Vector2 &other) const;				//Distance squared for efficient comparison	
																			
	//Normalise																
	static Vector2	normalise(const Vector2 &vec);							//Returns a normalised copy of input vector							 		
	void			normalise();											//Self normalise
	Vector2			normaliseCpy() const;									//Returns a normalised copy of this vector
	
	//Absolute	
	static Vector2	getAbsolute(const Vector2 &vec);						//Returns an absolute copy of input vector
	void			absolute();												//Self absolute
	Vector2			absoluteCpy() const;									//Returns an absolute copy of current vector
};

}
