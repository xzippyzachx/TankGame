#pragma once
#include <functional>
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

	bool operator==(const Vector2 &v) const
	{
		return (x == v.x && y == v.y);
	}

	struct HashFunction
	{
		size_t operator()(const Vector2& v) const
		{
			return (std::hash<float>()(v.x) ^ (std::hash<float>()(v.y) << 1));
		}
	};
};
