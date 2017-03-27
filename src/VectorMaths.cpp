// Vector Class
#include "VectorMaths.h"
#include <math.h>
#include <iostream>

// Constructor
Vec3::Vec3() {
	x = 0;
	y = 0;
	z = 0;
}

Vec3::Vec3(float xVal, float yVal, float zVal) {
	x = xVal;
	y = yVal;
	z = zVal;
}

// Public
// Vector operators
bool Vec3::operator==(Vec3 vector) {
	if (x == vector.x && y == vector.y && z == vector.z) {
		return true;
	}
	else {
		return false;
	}
}

Vec3 Vec3::operator+(Vec3 vector) {
	return Vec3(x + vector.x, y + vector.y, z + vector.z);
}

Vec3 Vec3::operator-(Vec3 vector) {
	return Vec3(x - vector.x, y - vector.y, z - vector.z);
}

Vec3 Vec3::operator*(Vec3 vector) {
	return Vec3(0, 0, 0);
}

Vec3 Vec3::operator/(Vec3 vector) {
	return Vec3(0, 0, 0);
}

Vec3 Vec3::cross(Vec3 vector) {
	return Vec3(y * vector.z - z * vector.y,
		z * vector.x - x * vector.z,
		x * vector.y - y * vector.x);
}

float Vec3::dot(Vec3 vector) {
	return (x * vector.x + y * vector.y + z * vector.z);
}

float Vec3::length() {
	return float(sqrt(x*x + y*y + z*z));
}

// 	Scalar operators
Vec3 Vec3::operator+(float scalar)
{
	return Vec3(x + scalar, y + scalar, z + scalar);
}

Vec3 Vec3::operator-(float scalar)
{
	return Vec3(x - scalar, y - scalar, z - scalar);
}

Vec3 Vec3::operator*(float scalar)
{
	return Vec3(x * scalar, y * scalar, z * scalar);
}

Vec3 Vec3::operator/(float scalar)
{
	return Vec3(x / scalar, y / scalar, z / scalar);
}

// Protected
// Private

// Destructor
Vec3::~Vec3() {

}

