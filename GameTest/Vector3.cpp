#include "stdafx.h"
#include "Vector3.h"

Vector3::Vector3()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

Vector3::Vector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3 Vector3::operator+(const Vector3& vect3)
{
	return Vector3(x + vect3.x, y + vect3.y, z + vect3.z);
}

float Vector3::Dot(const Vector3& vect3)
{
	return vect3.x * x + vect3.y * y + vect3.z * z;
}
