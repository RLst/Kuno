//pkr Math Library
//Author: Tony Le
//Version: 1.0

#include <cmath>
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

namespace pkr {

	const float Vector3::DEF_TOLERANCE = 0.00001f;

Vector3::Vector3() : x(0), y(0), z(0)							//Default
{}

Vector3::Vector3(float x, float y, float z) : x{x}, y{y}, z{z}	//Initialise
{}

Vector3::Vector3(const Vector2 & other) :						//2D Copy
	x{other.x}, y{other.y}, z{1}			//Copy other into this, Z is set to vector flag (1)
{}

Vector3::Vector3(const Vector3 & other)	:						//3D Copy
	x{other.x}, y{other.y}, z{other.z}		//Copy other into this
{}

Vector3::Vector3(const Vector4 & other) :						//4D Copy
	x{other.x}, y{other.y}, z{other.z}		//Copy other into this, ignore other.w
{}

Vector3::~Vector3()											//Destructor
{}

Vector3 Vector3::operator-() const
{
	return { -x, -y, -z };
}

Vector3 Vector3::operator+(const Vector3 & other) const		//Addition
{
	return { x + other.x, y + other.y, z + other.z };
}

Vector3 Vector3::operator-(const Vector3 & other) const		//Subtract
{
	return { x - other.x, y - other.y, z - other.z };
}

Vector3 Vector3::operator*(const float scalar) const		//POST multiply
{
	return { x * scalar, y * scalar, z * scalar };
}

Vector3 Vector3::operator/(float scalar) const				//POST divide
{
	//What about divide by 0?
	return { x / scalar, y / scalar, z / scalar };
}

Vector3 operator*(float scalar, const Vector3 & other)		//PRE multiply
{
	return { other.x * scalar, other.y * scalar, other.z * scalar };
}

Vector3& Vector3::operator+=(const Vector3 & other)			//Addition assign
{
	x += other.x; y += other.y; z += other.z;
	return *this;
}

Vector3& Vector3::operator-=(const Vector3 & other)			//Subtract assign
{
	x -= other.x; y -= other.y; z -= other.z;
	return *this;
}

Vector3& Vector3::operator*=(const float scalar)			//Scalar multiply assign
{
	x *= scalar; y *= scalar; z *= scalar;
	return *this;
}

Vector3& Vector3::operator/=(const float scalar)			//Scalar divide assign
{
	x /= scalar; y /= scalar; z /= scalar;
	return *this;
}

Vector3& Vector3::operator=(const Vector3 & other)			//Assignment
{
	x = other.x;
	y = other.y;
	z = other.z;
	return *this;
}

bool Vector3::operator==(const Vector3 & other)				//Equality check
{
	return (x == other.x && y == other.y && z == other.z);
}

bool Vector3::operator!=(const Vector3 & other)				//Non equality check
{
	return (x != other.x && y != other.y && z != other.z);
}

bool Vector3::equal(const Vector3 & other, float tolerance)	//Equality check with tolerance
{
	if (abs(x - other.x) >= tolerance &&
		abs(y - other.y) >= tolerance &&
		abs(z - other.z) >= tolerance)
		return false;	//Out of tolerance (too much difference)
	return true;	//Within tolerance
}

bool Vector3::notEqual(const Vector3 & other, float tolerance)	//Inequality check with tolerance
{
	if (abs(x - other.x) < tolerance &&
		abs(y - other.y) < tolerance &&
		abs(z - other.z) < tolerance) 
		return false;	//Out of tolerance (not enough difference)
	return true;	//Within tolerance
}

float Vector3::operator[]( int index) const						//Inspector 
{
	return data[index];
}

float & Vector3::operator[]( int index)							//Mutator (Return reference)
{
	return data[index];
}

Vector3::operator float*()										//Mutator float pointer cast
{
	return &data[0];
}

Vector3::operator const float*() const							//Inspector float pointer cast
{
	return data;
}

float Vector3::dot(const Vector3 & a, const Vector3 & b)		//Static Dot product
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

float Vector3::dot(const Vector3 & other) const					//Dot product
{
	return x * other.x + y * other.y + z * other.z;
}

Vector3 Vector3::cross(const Vector3 & a, const Vector3 & b)	//Static Cross product
{
	return{ a.y * b.z - a.z * b.y,
			a.z * b.x - a.x * b.z,
			a.x * b.y - a.y * b.x };
}

Vector3 Vector3::cross(const Vector3 & other) const				//Cross product
{
	return{ y * other.z - z * other.y,
			z * other.x - x * other.z,
			x * other.y - y * other.x };
}

float Vector3::angleBetween(const Vector3 & a, const Vector3 & b)		//Static angle between two input vectors
{
	//Normalise and calculate the dot product
	float d = dot(normalise(a), normalise(b));
	return acos(d);
}

float Vector3::angleBetween(const Vector3& other) const			//Angle between another
{
	//Normalise first
	Vector3 a = this->normaliseCpy();
	Vector3 b = other.normaliseCpy();

	//Calculate dot product
	float d = a.x * b.x + a.y * b.y + a.z * b.z;

	//Return the angle between them
	return acos(d);
}

float Vector3::magnitude(const Vector3 & vec)					//Static magnitude of input vector
{
	return sqrt(vec.x*vec.x + vec.y*vec.y + vec.z*vec.z);
}

float Vector3::magnitude()										//Magnitude
{
	return sqrt(x*x + y*y + z*z);
}

float Vector3::magnitudeSqr() const								//Magnitude squared
{
	return (x*x + y*y + z*z);
}

void Vector3::setMagnitude(float mag)
{
	//Normalise then scalar multiply by magnitude
	normalise();
	*this *= mag;
}

float Vector3::distance(const Vector3 & a, const Vector3 & b)	//Static distance between input vectors
{
	float diffX = a.x - b.x;
	float diffY = a.y - b.y;
	float diffZ = a.z - b.z;
	return sqrt(diffX * diffX + diffY * diffY + diffZ * diffZ);
}

float Vector3::distance(const Vector3 & other) const			//Distance
{
	float diffX = x - other.x;
	float diffY = y - other.y;
	float diffZ = z - other.z;
	return sqrt(diffX*diffX + diffY*diffY + diffZ*diffZ);
}

float Vector3::distanceSqr(const Vector3& vec) const			//Distance squared
{
	float diffX = x - vec.x;
	float diffY = y - vec.y;
	float diffZ = z - vec.z;
	return (diffX * diffX + diffY * diffY + diffZ * diffZ);
}

Vector3 Vector3::normalise(const Vector3& vec)					//Static normalised copy of input vectors
{
	//In case of divide by zero
	if (vec.x == 0.0f && vec.y == 0.0f && vec.z == 0.0f)
		return { 0, 0, 0 };

	float mag = sqrt(vec.x*vec.x + vec.y*vec.y + vec.z*vec.z);
	return { vec.x / mag, vec.y / mag, vec.z / mag };
}

void Vector3::normalise()										//Self normalise
{
	//In case of divide by zero
	if (x == 0.0f && y == 0.0f && z == 0.0f)
		return;

	float mag = sqrt(x*x + y*y + z*z);
	x /= mag;
	y /= mag;
	z /= mag;
}

Vector3 Vector3::normaliseCpy() const							//Normalised copy
{
	float mag = sqrt(x * x + y * y + z * z);
	return { x / mag, y / mag, z / mag };
}

Vector3 Vector3::absolute(const Vector3 & vec)					//Static absolute copy of input vector
{
	Vector3 result;
	for (int i = 0; i < 3; ++i)
		result.data[i] = abs(vec.data[i]);
	return result;
}

void Vector3::absolute()										//Self absolute
{	
	for (int i = 0; i < 3; ++i)
		data[i] = abs(data[i]);
}

Vector3 Vector3::absoluteCpy() const							//Absolute copy
{
	Vector3 result;
	for (int i = 0; i < 3; ++i)
		result.data[i] = abs(data[i]);
	return result;
}

}
