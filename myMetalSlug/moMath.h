#pragma once

#include <math.h>

struct Vector2
{
	static Vector2 Up;
	static Vector2 Right;

	static Vector2 One;
	static Vector2 Zero;

	float x;
	float y;

	Vector2()
		: x(0.0f)
		, y(0.0f)
	{

	}
	Vector2(float x, float y)
		: x(x)
		, y(y)
	{

	}
	Vector2(int x, int y)
		: x(x)
		, y(y)
	{

	}
	Vector2(const Vector2&) = default;
	Vector2& operator=(const Vector2&) = default;

	Vector2(Vector2&&) = default;
	Vector2& operator=(Vector2&&) = default;

	Vector2& operator+(const Vector2& other) {
		Vector2 temp;
		temp.x = x + other.x;
		temp.y = y + other.y;
		return temp;
	}
	Vector2& operator-(const Vector2& other) {
		Vector2 temp;
		temp.x = x - other.x;
		temp.y = y - other.y;
		return temp;
	}
	void operator +=(const Vector2& other) {

		x += other.x;
		y += other.y;
	}
	void operator-=(const Vector2& other) {
		
		x -=other.x;
		y -= other.y;
	}

	float Length() {
		return sqrt(x * x + y * y);
	}

	Vector2& Nomalize() {
		float mLength = Length();

		x /= mLength;
		y /= mLength;
		return *this;
	
	}

};

