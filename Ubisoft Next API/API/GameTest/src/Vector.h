#pragma once
#include <cmath>


struct  Vector3;
struct Vector2
{
	float x =0;
	float y =0;


	Vector2() : x(0), y(0) {}

	//Vector2(const Vector3& other)
	//{
	//	this->x = other.x;
	//	this->y = other.y;
	//}

	Vector2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}


	 static float Dot(const Vector2& lhs, const Vector2& rhs) 
	{
		return lhs.x * rhs.x + lhs.y * rhs.y;
	}

	float Magnitude() const {
		return std::sqrt(x * x + y * y);
	}
	float LengthSquared() const {
		return Dot(*this, *this);
	}
	Vector2 Normalize() 
	{
		float magnitude = Magnitude();
		if (magnitude > 1e-6f) 
		{
			return Vector2(x / magnitude, y / magnitude);
		}
		return Vector2::Zero();
	}
	static Vector2 Normalize(const Vector2 other)
	{
		float magnitude = other.Magnitude();

		if (magnitude > 1e-6f)
		{
			return Vector2(other.x / magnitude, other.y / magnitude);
		}

		return Vector2::Zero();
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

	static Vector2 Reflect(Vector2& incident, Vector2& normal) {
		Vector2 norm = normal;
		float dotProduct = Vector2::Dot(incident, norm);
		return incident - norm * (2.0f * dotProduct);
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


	Vector2& operator+=(const Vector2& other) {
		
		this->x += other.x;
		this->y += other.y;
		return *this;
	}

	Vector2& operator-=(const Vector2& other) {

		this->x -= other.x;
		this->y -= other.y;
		return *this;
	}

	Vector2& operator*=(const  float& value) {

		this->x *= value;
		this->y *= value;
		return *this;
	}

	bool operator!=(const Vector2& other)
	{
		return !(x == other.x && y == other.y);
	}

	bool operator==(const Vector2& other)
	{
		return (x == other.x && y == other.y);
	}

	static float Cross(const Vector2& current, const Vector2& other) {
		return current.x * other.y - current.y * other.x;
	}

	float& operator[](int index) {
		if (index == 0) return x;
		if (index == 1) return y;
		throw std::out_of_range("Index out of range for Vector2");
	}

	// Const access by index
	const float& operator[](int index) const {
		if (index == 0) return x;
		if (index == 1) return y;
		throw std::out_of_range("Index out of range for Vector2");
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

	static Vector3 Normalize(const Vector3 other)
	{
		float magnitude = other.Magnitude();

		if (magnitude > 1e-6f)
		{
			return Vector3(other.x / magnitude, other.y / magnitude, other.z / magnitude);
		}

		return Vector3::Zero();
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
		if (this != &other) { 
			x = other.x;
			y = other.y;
			z = other.z;
		}
		return *this; 
	}

	Vector3& operator+=(const Vector3& other) {
		this->x += other.x;
		this->y += other.y;
		this->z += other.z;
		return *this;
	}

	Vector3& operator-=(const Vector3& other) {
		this->x -= other.x;
		this->y -= other.y;
		this->z -= other.z;
		return *this;
	}

};