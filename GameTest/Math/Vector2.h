#pragma once
class Vector2
{
public:
	float x, y;
	Vector2();
	Vector2(float x, float y);
	float GetMagnitude();

	inline Vector2 Vector2::operator * (float v) { return Vector2(x * v, y * v); }
};
