#pragma once

#include <string>
#include <iostream>>
#include <math.h>
#include <algorithm>

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

	Vector2 Lerp(const Vector2& a, const Vector2& b, float t)
	{
		t = std::clamp(t, 0.0f, 1.0f);
		return {
			a.x + (b.x - a.x) * t,
			a.y + (b.y - a.y) * t
		};
	}


	Vector2 operator*(float s) const
	{
		return  Vector2(x*s,y*s);
	}


	Vector2 operator+(Vector2 const& a) const
	{
		return  Vector2(x + a.x, y + a.y);
	}
	Vector2 operator-(Vector2 const& a) const
	{
		return  Vector2(x - a.x, y - a.y);
	}
	//Returns distance but sqrt is bad and slow so avoid if possible
	static float Distance(Vector2 a, Vector2 b);


	std::string Print()
	{
		return std::to_string(x) + "," + std::to_string(y);
	}

};

#pragma endregion



struct Collider
{
	~Collider() {}
};



//Real time collision Dection page 79
#pragma region AABB 

struct AABB : Collider
{
private:
	Vector2 m_min;
	Vector2 m_max;
	std::weak_ptr<Ctransform> m_transform;
public:

	AABB(GameObject& go, Vector2 min, Vector2 max);

	



	const Vector2 GetMin() const;

	const Vector2 GetMax() const;
	  
	//Checks to see if there is an intersection between boxes
	static bool CheckAABBCollision(AABB a, AABB b);


};
#pragma endregion

#pragma region Circle

struct Circle : Collider
{
	Vector2 m_position;
	std::weak_ptr<Ctransform> m_transform;
public:

	float m_radius;
	Circle(GameObject& go, float radius, Vector2 position);


	const Vector2 GetPosition() const;

	
	bool CheckCircleCollision(Circle a, Circle b)

	{

		float r = a.m_radius + b.m_radius;

		r *= r;

		return r < (std::pow((a.GetPosition().x + b.GetPosition().x),2)  + std::pow((a.GetPosition().y + b.GetPosition().y) ,2));
	}

};


#pragma endregion


//float LinearTween(float t,float b,float c,float d)
//{
//	return c * t / d + b;
//}


