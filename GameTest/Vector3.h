#pragma once
struct Vector3
{
    float x, y, z;

    Vector3();

    Vector3(float x, float y, float z);

    Vector3 operator + (const Vector3& vect3);

    float Dot(const Vector3& vect3);
};
