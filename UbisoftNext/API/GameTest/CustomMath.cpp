#pragma once
#include "stdafx.h"
#include "CustomMath.h"
#include "GameObject.h"


#pragma region Vector2

const Vector2 Vector2::UP(0, 1);
const Vector2 Vector2::DOWN(0, -1);
const Vector2 Vector2::RIGHT(1, 0);
const Vector2 Vector2::LEFT(-1, 0);


float Vector2::Distance(Vector2 a, Vector2 b)
{
	return sqrt(((a.x - b.x) * (a.x - b.x)) +
		((a.y - b.y) * (a.y - b.y)));
}


#pragma endregion

#pragma region AABB
AABB::AABB(GameObject& go, Vector2 min, Vector2 max) : m_transform(go.GetComponent<Ctransform>()), m_min(min), m_max(max) {}

const Vector2 AABB::GetMin() const
{
	if (std::shared_ptr<Ctransform> transform = m_transform.lock()) // this checks if m_transform still exists and creates a shared pointer to it , supposed to be safer  
	{
		return m_min + transform->GetPosition();
	}
	return m_min;
}


const Vector2 AABB::GetMax() const {

	if (std::shared_ptr<Ctransform>  transform = m_transform.lock()) // this checks if m_transform still exists and creates a shared pointer to it , supposed to be safer  
	{
		return m_max + transform->GetPosition();
	}
	return m_max;

}

#pragma endregion

bool AABB::CheckAABBCollision(AABB a, AABB b)
{
	
	
	if (a.GetMax().x < b.GetMin().x or a.GetMin().x > b.GetMax().x) return false;

	if (a.GetMax().y < b.GetMin().y or a.GetMin().y > b.GetMax().y) return false;

	return true;

	

}

Circle::Circle(GameObject& go, float radius, Vector2 position) : m_transform(go.GetComponent<Ctransform>()), m_radius(radius), m_position(position) {}

