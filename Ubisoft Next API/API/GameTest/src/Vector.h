#pragma once
#include <cmath>

struct Vector2
{
	float x;
	float y;

	Vector2() : x(0), y(0) {}

	Vector2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	float Dot(const Vector2& other) const {
		return x * other.x + y * other.y;
	}
	float Magnitude() const {
		return std::sqrt(x * x + y * y);
	}
	Vector2 Normalize() 
	{
		float magnitude = Magnitude();
		if (magnitude != 0.0f)
		{
			x /= magnitude;
			y /= magnitude;
		}
		return Vector2(x, y);
	}

	static Vector2 Zero()
	{
		return { 0,0 };
	}

	static Vector2 Right()
	{
		return { 1,0 };
	}

	static Vector2 Up() 
	{
		return { 0,1 };
	}

	Vector2 operator+(const Vector2& other) const {
		return Vector2(x + other.x, y + other.y);
	}
	Vector2 operator-(const Vector2& other) const {
		return Vector2(x - other.x, y - other.y);
	}
	Vector2 operator*(float scalar) const {
		return Vector2(x * scalar, y * scalar);
	}
	Vector2 operator/(float scalar) const {
		if (scalar == 0) 
		{
			return Vector2(0, 0);
		}
		return Vector2(x / scalar, y / scalar);
	}

};