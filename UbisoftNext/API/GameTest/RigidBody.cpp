#include "stdafx.h"
#include "RigidBody.h"
#include "Collider.h"
namespace physics
{
	RigidBody RigidBody::CreateCircleRigidBody(bool is_static, float radius, float density, Material material)
	{
		float area = PI * radius * radius;

		if (area < MIN_BODY_SIZE)
		{
			return NULL;
		}


		RigidBody body = RigidBody(is_static, physics::Shape::CIRCLE, physics::Circle(radius), material, MassData(area * density));

		return body;
	}

	RigidBody RigidBody::CreateAABBRigidBody(bool is_static, float length, float width, float density,
		Material material)
	{
		float area = width * length;
		float mass = area * density;

		RigidBody body = RigidBody(is_static, physics::Shape::BOX, physics::AABB(length, width), material, MassData(area * density));

		return body;
	}
};
