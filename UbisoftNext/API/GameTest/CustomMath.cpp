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



Vector2 operator*(float s, const Vector2& v)
{
	return  Vector2(v.x * s, v.y * s);
}

