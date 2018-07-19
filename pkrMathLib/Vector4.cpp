//pkr Math Library
//Author: Tony Le
//Version: 1.0

#include "Vector4.h"
#include "Vector3.h"
#include <cmath>

namespace pkr {

const float Vector4::DEF_TOLERANCE = 0.00001f;

Vector4::Vector4() : x(0), y(0), z(0), w(0)							//Default
{}

Vector4::Vector4(float x, float y, float z, float w) : x{x}, y{y}, z{z}, w{w}	//Initialisation; automatic 3D or 4D
{}

Vector4::Vector4(const Vector3 & other) :							//3D Copy constructor
	x{other.x}, y{other.y}, z{other.z}, w{1}	//Copy Vector3 into this Vector4
{}

Vector4::Vector4(const Vector4 & other)	:							//4D Copy constructor
	x{other.x}, y{other.y}, z{other.z}, w{other.w}	//Copy Vector4 into this Vector4
{}

Vector4::~Vector4()													//Destructor
{}

Vector4 Vector4::operator-() const
{
	return { -x, -y, -z, -w };
}

Vector4 Vector4::operator+(const Vector4 & other) const				//Addition
{
	return { x + other.x, y + other.y, z + other.z , w + other.w };
}

Vector4 Vector4::operator-(const Vector4 & other) const				//Subtract
{
	return { x - other.x, y - other.y, z - other.z, w - other.w };
}

Vector4 Vector4::operator*(const float scalar) const				//POST multiply
{
	return { x * scalar, y * scalar, z * scalar, w * scalar };
}

Vector4 Vector4::operator/(float scalar) const						//POST divide
{
	//What about divide by 0?
	return { x / scalar, y / scalar, z / scalar, w * scalar };
}

Vector4 operator*(float scalar, const Vector4 & other)				//PRE multiply
{
	return { other.x * scalar, other.y * scalar, other.z * scalar, 0 };
}

Vector4 operator/(float scalar, const Vector4 & other)				//PRE divide
{
	return { other.x / scalar, other.y / scalar, other.z / scalar, 0 };
}


Vector4& Vector4::operator+=(const Vector4 & other)					//Addition assign
{
	x += other.x; 
	y += other.y; 
	z += other.z; 
	w += other.z;
	return *this;
}

Vector4& Vector4::operator-=(const Vector4 & other)					//Subtract assign
{
	x -= other.x; 
	y -= other.y; 
	z -= other.z; 
	w -= other.w;
	return *this;
}

Vector4& Vector4::operator*=(const float scalar)					//Scalar multiply assign
{
	x *= scalar; 
	y *= scalar; 
	z *= scalar; 
	w *= scalar;
	return *this;
}

Vector4& Vector4::operator/=(const float scalar)					//Scalar divide assign
{
	x /= scalar; 
	y /= scalar; 
	z /= scalar;
	w /= scalar;
	return *this;
}

Vector4 & Vector4::operator=(const Vector3 & other)
{
	x = other.x;
	y = other.y;
	z = other.z;
	w = 1;
	return *this;
}

Vector4& Vector4::operator=(const Vector4 & other)					//Assign
{
	x = other.x;
	y = other.y;
	z = other.z;
	w = other.w;
	return *this;
}

bool Vector4::operator==(const Vector4 & other)						//Equality check
{
	return (x == other.x && y == other.y && z == other.z && w == other.w);
}

bool Vector4::operator!=(const Vector4 & other)						//Inequality check
{
	return (x != other.x && y != other.y && z != other.z && w != other.w);
}

bool Vector4::equal(const Vector4 & other, float tolerance)			//Equality check with tolerance
{
	if (abs(x - other.x) >= tolerance &&
		abs(y - other.y) >= tolerance &&
		abs(z - other.z) >= tolerance &&
		abs(w - other.w) >= tolerance)
		return false;	//Out of tolerance (too much difference)	
	return true;	//Within tolerance
}

bool Vector4::notEqual(const Vector4 & other, float tolerance)		//Inequality check with tolerance
{
	if (abs(x - other.x) < tolerance &&
		abs(y - other.y) < tolerance &&
		abs(z - other.z) < tolerance &&
		abs(w - other.w) < tolerance)
		return false;	//Out of tolerance (not enough difference)
	return true;	//Within tolerance
}

float Vector4::operator[](int index) const							//Access 
{
	return data[index];
}

float & Vector4::operator[](int index)								//Return reference
{
	return data[index];
}

Vector4::operator float*()											//Mutable float pointer cast
{
	return &data[0];
}

Vector4::operator const float*() const								//Inspector float pointer cast
{
	return data;
}

float Vector4::dot(const Vector4 & a, const Vector4 & b)			//Static dot product
{
	return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

float Vector4::dot(const Vector4 & other) const						//Dot product
{
	return x * other.x + y * other.y + z * other.z + w * other.w;
}

Vector4 Vector4::cross(const Vector4 & a, const Vector4 & b)		//Static cross product
{
	return{ a.y * b.z - a.z * b.y,
			a.z * b.x - a.x * b.z,
			a.x * b.y - a.y * b.x,
			0 };
}

Vector4 Vector4::cross(const Vector4 & other) const					//Cross product
{
	return{ y * other.z - z * other.y,
			z * other.x - x * other.z,
			x * other.y - y * other.x, 
			0};
}

float Vector4::angleBetween(const Vector4 & a, const Vector4 & b)	//Angle between non-members
{
	//Normalise and calculate the dot product
	float d = dot(normalise(a), normalise(b));
	return acos(d);
}

float Vector4::angleBetween(const Vector4 & other) const			//Angle between
{
	//Normalise first
	Vector4 a = this->normaliseCpy();
	Vector4 b = other.normaliseCpy();

	//Calculate dot product
	float d = a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;

	//Return the angle between them
	return acos(d);
}

float Vector4::magnitude(const Vector4 & vec)						//Static magnitude of input vector
{
	return sqrt(vec.x*vec.x + vec.y*vec.y + vec.z*vec.z + vec.w*vec.w);
}

float Vector4::magnitude()											//Magnitude
{
	return sqrt(x*x + y*y + z*z + w*w);	
}

float Vector4::magnitudeSqr() const									//Magnitude
{
	return (x*x + y*y + z*z + w*w);
}

void Vector4::setMagnitude(float mag)
{
	//Normalise then scalar multiply by magnitude
	normalise();
	*this *= mag;
}

float Vector4::distance(const Vector4 & a, const Vector4 & b)		//Static distance between input vector
{
	float diffX = a.x - b.x;
	float diffY = a.y - b.y;
	float diffZ = a.z - b.z;
	float diffW = a.w - b.w;
	return sqrt(diffX*diffX + diffY * diffY + diffZ * diffZ + diffW * diffW);
}

float Vector4::distance(const Vector4 & vec) const					//Distance
{
	float diffX = x - vec.x;
	float diffY = y - vec.y;
	float diffZ = z - vec.z;
	float diffW = w - vec.w;
	return sqrt(diffX*diffX + diffY*diffY + diffZ*diffZ + diffW*diffW);
}

float Vector4::distanceSqr(const Vector4 & vec) const				//Distance squared
{
	float diffX = x - vec.x;
	float diffY = y - vec.y;
	float diffZ = z - vec.z;
	float diffW = w - vec.w;
	return (diffX*diffX + diffY*diffY + diffZ*diffZ + diffW*diffW);
}

Vector4 Vector4::normalise(const Vector4 & vec)					//Static normalised copy of input vector
{
	//In case of divide by zero
	if (vec.x == 0.0f && vec.y == 0.0f &&vec.z == 0.0f)
		return { 0,0,0 };

	float mag = sqrt(vec.x*vec.x + vec.y*vec.y + vec.z*vec.z);
	return { vec.x / mag, vec.y / mag, vec.z / mag };
}

void Vector4::normalise()											//Self normalise
{
	//In case of divide by zero
	if (x == 0.0f && y == 0.0f && z == 0.0f && w == 0.0f)
		return;

	float mag = sqrt(x*x + y*y + z*z + w*w);
	//Unit V = V / |V|
	x /= mag;
	y /= mag;
	z /= mag;
	w /= mag;
}

Vector4 Vector4::normaliseCpy() const								//Normalised copy
{
	float mag = sqrt(x * x + y * y + z * z + w * w);
	return { x / mag, y / mag, z / mag, w / mag };
}

Vector4 Vector4::absolute(const Vector4 & vec)						//Static absolute copy of input vector
{
	Vector4 result;
	for (int i = 0; i < 4; ++i)
		result.data[i] = abs(vec.data[i]);
	return result;
}

void Vector4::absolute()											//Self absolute
{
	for (int i = 0; i < 4; ++i)
		data[i] = abs(data[i]);
}

Vector4 Vector4::absoluteCpy() const								//Absolute copy
{
	Vector4 result;
	for (int i = 0; i < 4; ++i)
		result.data[i] = abs(data[i]);
	return result;
}

}
