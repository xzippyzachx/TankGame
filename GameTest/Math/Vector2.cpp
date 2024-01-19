#include "stdafx.h"
#include "Vector2.h"

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

float Vector2::GetMagnitude()
{
	return x * x + y * y;
}
