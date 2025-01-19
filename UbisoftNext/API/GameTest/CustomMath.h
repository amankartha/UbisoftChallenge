#pragma once

#include <string>
#include <iostream>
#include <math.h>
#include <algorithm>
#include <unordered_map>
#include <functional>

class GameObject;
class Ctransform;

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
	

	void Reset()
	{
		x = 0.0f;
		y = 0.0f;
	}

	float Magnitude() const {
		return std::sqrt(x * x +y * y);
	}
	float MagnitudeSquared() const
	{
		return x * x + y * y;
	}
	
	static float Magnitude(Vector2 vector2);

	Vector2 Normalize() const {
		float mag = Magnitude();
		return (mag > 0) ? Vector2(x / mag, y / mag) : Vector2();
	}

	static Vector2 Normalize(Vector2 v2);


	static float Dot(Vector2 a, Vector2 b);


	//Taken from Unity API : v = inDirection - 2 * inNormal * dot(inDirection inNormal). 
	//returns the reflection based on the normal
	Vector2 Reflect(Vector2 inDir, Vector2 inNorm)
	{
		return inDir - inNorm * (2 * Dot(inDir, inNorm));
	}

	Vector2 Lerp(const Vector2& a, const Vector2& b, float t)
	{
		t = std::clamp(t, 0.0f, 1.0f);
		return {
			a.x + (b.x - a.x) * t,
			a.y + (b.y - a.y) * t
		};
	}

	bool operator==(const Vector2& other) const {
		return x == other.x && y == other.y;
	}

	Vector2 operator*(float s) const
	{
		return  Vector2(x*s,y*s);
	}

	Vector2 operator/(float s) const
	{
		return  Vector2(x / s, y / s);
	}

	Vector2 operator+(Vector2 const& a) const
	{
		return  Vector2(x + a.x, y + a.y);
	}
	Vector2& operator+=(const Vector2& other) {
		x += other.x;
		y += other.y;
		return *this;
	}
	Vector2& operator-=(const Vector2& other) {
		x -= other.x;
		y -= other.y;
		return *this;
	}
	Vector2 operator-(Vector2 const& a) const
	{
		return  Vector2(x - a.x, y - a.y);
	}


	//Returns distance but sqrt is bad and slow so avoid if possible
	static float Distance(Vector2 a, Vector2 b);

	static float DistanceSquared(Vector2 a, Vector2 b);

	std::string Print()
	{
		return std::to_string(x) + "," + std::to_string(y);
	}

};





//Custom hash needed so I can use Vector2s as a key

template <>
struct std::hash<Vector2> {
	size_t operator()(const Vector2& v) const {
		return hash<int>()(static_cast<int>(v.x)) ^ (hash<int>()(static_cast<int>(v.y)) << 1);
	}
};


struct IntVector2 {
	int x;
	int y;

	
	IntVector2(int x = 0, int y = 0) : x(x), y(y) {}


	static const IntVector2 UP;
	static const IntVector2 DOWN;
	static const IntVector2 LEFT;
	static const IntVector2 RIGHT;

	
	int SquaredMagnitude() const {
		return x * x + y * y;
	}

	
	int Dot(const IntVector2& a) const {
		return a.x * x + a.y * y;
	}

	
	IntVector2 Reflect(const IntVector2& inDir, const IntVector2& inNorm) const {
		int dotProduct = inDir.Dot(inNorm);
		return inDir - (inNorm * (2 * dotProduct));
	}

	
	IntVector2 Lerp(const IntVector2& a, const IntVector2& b, float t) const {
		t = std::clamp(t, 0.0f, 1.0f);
		return IntVector2(
			static_cast<int>(a.x + (b.x - a.x) * t),
			static_cast<int>(a.y + (b.y - a.y) * t)
		);
	}

	
	bool operator==(const IntVector2& other) const {
		return x == other.x && y == other.y;
	}

	IntVector2 operator*(int s) const {
		return IntVector2(x * s, y * s);
	}



	IntVector2 operator+(const IntVector2& a) const {
		return IntVector2(x + a.x, y + a.y);
	}

	IntVector2 operator-(const IntVector2& a) const {
		return IntVector2(x - a.x, y - a.y);
	}

	// Static method for distance (Manhattan distance for integers)
	static int Distance(const IntVector2& a, const IntVector2& b) {
		return std::abs(a.x - b.x) + std::abs(a.y - b.y);
	}

	
	std::string Print() const {
		return std::to_string(x) + "," + std::to_string(y);
	}
};



// Custom hash needed to use IntVector2 as a key in std::unordered_map
namespace std {
	template <>
	struct hash<IntVector2> {
		size_t operator()(const IntVector2& v) const {
			
			return std::hash<int>()(v.x) ^ std::hash<int>()(v.y << 1);
		}
	};
}


#pragma endregion

struct Transform
{
	Vector2 position;
	float angle;
	float scale;

	Transform(float x = 0.0f, float y = 0.0f,float a = 0.0f,float s = 1.0f) {
		position.x = x;
		position.y = y;
		angle = a;
		scale = 1.0f;
	}

	void ResetTransform()
	{
		position.x = 0;
		position.y = 0;
		angle = 0;
		scale = 1.0f;
	}

	bool operator==(const Transform& other) const {
		return position == other.position &&
			std::abs(angle - other.angle) < 1e-6 &&     //cus they floats
			std::abs(scale - other.scale) < 1e-6;
	}


	bool operator!=(const Transform& other) const {
		return !(*this == other);
	}


	Transform operator+(const Transform& other) const {
		return Transform(
			position.x + other.position.x,
			position.y + other.position.y,
			angle + other.angle,
			scale * other.scale
		);
	}

	
	Transform operator-(const Transform& other) const {
		return Transform(
			position.x - other.position.x,
			position.y - other.position.y,
			angle - other.angle,
			scale / other.scale
		);
	}


	Transform& operator+=(const Transform& other) {
		position += other.position;
		angle += other.angle;
		scale *= other.scale;
		return *this;
	}

	
	Transform& operator-=(const Transform& other) {
		position -= other.position;
		angle -= other.angle;
		scale /= other.scale;
		return *this;
	}
};





