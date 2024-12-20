#pragma once
#include <string>
#include <iostream>>
#include <math.h>


#pragma region VECTOR2


struct Vector2
{
	float x;
	float y;

	Vector2(float x = 0.0f, float y = 0.0f) : x(x), y(y) {}

	static const Vector2 UP; 
	static const Vector2 DOWN; 
	static const Vector2 LEFT; 
	static const Vector2 RIGHT; 
	
	//returns the magnitude of the vector 2
	float Magnitude() const {
		return std::sqrt(x * x * +y * y);
	}
	//Normalizes the vector 
	Vector2 Normalize() const {
		float mag = Magnitude();
		return (mag > 0) ? Vector2(x / mag, y / mag) : Vector2();
	}
	//Returns the Dot product of the two vectors
	float Dot(Vector2 a, Vector2 b) const
	{
		return a.x * b.x + a.y * b.y;
	}
	//Taken from Unity API : v = inDirection - 2 * inNormal * dot(inDirection inNormal). 
	//returns the reflection based on the normal
	Vector2 Reflect(Vector2 inDir, Vector2 inNorm)
	{
		return (inDir - (inNorm*2) * Dot(inDir, inNorm));
	}


	Vector2 operator*(float s) const
	{
		return  Vector2(x*s,y*s);
	}

	Vector2 operator+(Vector2 const& a)
	{
		return  Vector2(x + a.x, y + a.y);
	}
	Vector2 operator-(Vector2 const& a)
	{
		return  Vector2(x - a.x, y - a.y);
	}
	
	std::string Print()
	{
		return std::to_string(x) + "," + std::to_string(y);
	}

};


#pragma endregion

