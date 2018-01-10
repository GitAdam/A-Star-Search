#ifndef VECTOR_CLASS_H
#define VECTOR_CLASS_H

class Vec3 {
public:
	// Vector values
	float x, y, z;

	// Constructors
	Vec3();
	Vec3(float xVal, float yVal, float zVal);

	// Vector operator
	bool operator==(Vec3 vector);
	Vec3 operator+(Vec3 vector);
	Vec3 operator-(Vec3 vector);
	Vec3 operator*(Vec3 vector);
	Vec3 operator/(Vec3 vector);	
	Vec3 cross(Vec3 vector);
	float dot(Vec3 vector);
	float length();

	// Scalar operators
	Vec3 operator+(float scalar);
	Vec3 operator-(float scalar);
	Vec3 operator*(float scalar);
	Vec3 operator/(float scalar);

	// Destructor
	~Vec3();
protected:
private:
};

#endif
