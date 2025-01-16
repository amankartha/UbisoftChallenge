#include "stdafx.h"
#include "RigidBody.h"
#include "Collider.h"
namespace physics
{
	void RigidBody::SetCircleRigidBody(bool is_static, float radius, float density, Material material)
	{
		float area = PI * radius * radius;

		if (area < MIN_BODY_SIZE)
		{
			return ;
		}
		this->m_shape = Shape::CIRCLE;
		this->m_isStatic = is_static;
		this->m_collider = Circle(radius);
		this->m_material = material;
		this->m_massData = MassData(area * density);

	

		
	}

	void RigidBody::SetAABBRigidBody(bool is_static, float length, float width, float density,
		Material material)
	{
		float area = width * length;
		float mass = area * density;

		this->m_shape = Shape::CIRCLE;
		this->m_isStatic = is_static;
		this->m_collider = AABB(length,width);
		this->m_material = material;
		this->m_massData = MassData(area * density);
	}
};
