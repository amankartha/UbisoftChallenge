#include "stdafx.h"
#include "RigidBody.h"

#include <cassert>

#include "Collider.h"
namespace physics
{
	void RigidBody::Clear()
	{
	}

	void RigidBody::Start()
	{
	}

	void RigidBody::Update(float deltaTime)
	{

		Vector2 acceleration = m_force / m_massData.mass;
		m_linearVelocity += acceleration * deltaTime;

		AddFriction();
		OffsetPosition(m_linearVelocity * deltaTime);

		m_force.Reset();

		if (m_linearVelocity.MagnitudeSquared() < 0.0001f)
		{
			m_linearVelocity.Reset();
		}

		//TODO: rotation
	}


	Collider* RigidBody::GetCollider()
	{
		return m_collider;
	}

	void RigidBody::SetCircleRigidBody(bool is_static, float radius, float density, Material material)
	{
		float area = PI * radius * radius * 0.1f ;

		if (area < MIN_BODY_SIZE)
		{
			assert(" AREA TOO SMALL");
		}
		m_shape = Shape::CIRCLE; 
		m_isStatic = is_static;
		m_collider = new Circle(radius);
		SetMaterial(material);
		m_massData = MassData(area * density,is_static);
	}

	void RigidBody::SetAABBRigidBody(bool is_static, float width, float height, float density,
		Material material)
	{
		float area = width * height ;
		float mass = area * density;

		if (area < MIN_BODY_SIZE)
		{
			assert("AREA TOO SMALL");
		}
		m_shape = Shape::BOX;
		m_isStatic = is_static;
		m_collider = new AABB(width,height);
		SetMaterial(material);
		m_massData = MassData(area * density,is_static);
	}

	void RigidBody::AddFriction()
	{
		m_linearVelocity += m_linearVelocity.Normalize() * -1 * m_dynamic_friction;
	}
};
