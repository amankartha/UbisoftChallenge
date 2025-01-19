#include "stdafx.h"
#include "CustomMath.h"






const Vector2 Vector2::UP(0, 1);
const Vector2 Vector2::DOWN(0, -1);
const Vector2 Vector2::RIGHT(1, 0);
const Vector2 Vector2::LEFT(-1, 0);

const IntVector2 IntVector2::UP(0, 1);
const IntVector2 IntVector2::DOWN(0, -1);
const IntVector2 IntVector2::LEFT(-1, 0);
const IntVector2 IntVector2::RIGHT(1, 0);


float Vector2::Distance(Vector2 a, Vector2 b)
{
	return sqrt(((a.x - b.x) * (a.x - b.x)) +
		((a.y - b.y) * (a.y - b.y)));
}

float Vector2::DistanceSquared(Vector2 a, Vector2 b)
{
	return ((a.x - b.x) * (a.x - b.x)) +
		   ((a.y - b.y) * (a.y - b.y));
}


Vector2 operator*(float s, const Vector2& v)
{
	return  Vector2(v.x * s, v.y * s);
}

float Vector2::Magnitude(Vector2 vector2)
{
	return std::sqrt(vector2.x * vector2.x  +vector2.y * vector2.y);
}

Vector2 Vector2::Normalize(Vector2 v2)
{
	float mag = Magnitude(v2);
	return (mag > 0) ? Vector2(v2.x / mag, v2.y / mag) : Vector2();
}

float Vector2::Dot(Vector2 a, Vector2 b)
{
	return a.x * b.x + a.y * b.y;
}
