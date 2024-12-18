#pragma once
#include <cmath>

struct Vector2
{
	float x =0;
	float y =0;


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
	static Vector2 One()
	{
		return { 1,1 };
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

	Vector2& operator=(const Vector2& other) {
		if (this != &other) {
			x = other.x;
			y = other.y;
		}
		return *this;
	}

};

struct  Vector3
{
	float x;
	float y;
	float z;

	Vector3() : x(0), y(0) ,z(0){}
	Vector3(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	Vector3(const Vector2& other)
	{
		this->x = other.x;
		this->y = other.y;
		this->z = 0;
	}


	float Magnitude() const {
		return std::sqrt(x * x + y * y + z * z);
	}

	Vector3 Normalize()
	{
		float magnitude = Magnitude();

		if (magnitude != 0)
		{
			x /= magnitude;
			y /= magnitude;
			z /= magnitude;
		}

		return { x, y, z };
	}

	static Vector3 Zero()
	{
		return { 0,0 ,0 };
	}


	static Vector3 One()
	{
		return { 1,1 ,1 };
	}

	

	Vector3 operator+(const Vector3& other) const {
		return Vector3(x + other.x, y + other.y, z + other.z);
	}

	Vector3 operator+(const Vector2& other) const {
		return Vector3(x + other.x, y + other.y, z);
	}
	

	Vector3 operator-(const Vector3& other) const {
		return Vector3(x - other.x, y - other.y, z - other.z);
	}

	Vector3 operator*(float scalar) const {
		return Vector3(x * scalar, y * scalar, z* scalar);
	}
	Vector3 operator/(float scalar) const {
		if (scalar == 0)
		{
			return Vector3::Zero();
		}
		return Vector3(x / scalar, y / scalar, z / scalar);
	}

	Vector3& operator=(const Vector3& other) {
		if (this != &other) { // Avoid self-assignment
			x = other.x;
			y = other.y;
			z = other.z;
		}
		return *this; // Return the current object
	}


};