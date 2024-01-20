#include "stdafx.h"
#include "Vector2.h"
#include <cmath>

Vector2::Vector2()
{
	this->x = 0;
	this->y = 0;
}

Vector2::Vector2(float x, float y)
{
	this->x = x;
	this->y = y;
}

float Vector2::Length()
{
	return sqrt(x * x + y * y);
}

float Vector2::Distance(Vector2 v)
{
	return (v - Vector2(x, y)).Length();
}
