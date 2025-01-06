#pragma once
#include "stdafx.h"
#include "Collider.h"
#include "Ctransform.h"
#include "GameObject.h"

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


bool AABB::CheckAABBCollision(AABB a, AABB b)
{


	if (a.GetMax().x < b.GetMin().x or a.GetMin().x > b.GetMax().x) return false;

	if (a.GetMax().y < b.GetMin().y or a.GetMin().y > b.GetMax().y) return false;

	return true;



}

#pragma endregion

#pragma region Circle
Circle::Circle(GameObject& go, float radius, Vector2 position) : m_transform(go.GetComponent<Ctransform>()), m_radius(radius), m_position(position) {}

#pragma endregion

