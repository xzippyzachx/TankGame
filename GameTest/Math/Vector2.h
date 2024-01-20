#pragma once
class Vector2
{
public:
	float x, y;
	Vector2();
	Vector2(float x, float y);
	float Length();
	float Distance(Vector2 v);

	inline Vector2 Vector2::operator + (Vector2 v) { return Vector2(x + v.x, y + v.y); }
	inline Vector2 Vector2::operator - (Vector2 v) { return Vector2(x - v.x, y - v.y); }
	inline Vector2 Vector2::operator * (float v) { return Vector2(x * v, y * v); }
};
