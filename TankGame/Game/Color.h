#pragma once
struct Color
{
public:
	float r, g, b;

	inline Color() { this->r = 0.0f; this->g = 0.0f; this->b = 0.0f; }
	inline Color(float r, float g, float b) { this->r = r; this->g = g; this->b = b; }

	inline Color Color::operator = (Color & c) { r = c.r; g = c.g; b = c.b; return *this; }
};

