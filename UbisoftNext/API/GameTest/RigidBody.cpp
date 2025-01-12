#include "stdafx.h"
#include "RigidBody.h"
#include "Collider.h"
namespace physics
{
	std::shared_ptr<RigidBody> RigidBody::CreateCircleRigidBody(bool is_static, float radius, float density, Material material)
	{
		float area = PI * radius * radius;

		if (area < MIN_BODY_SIZE)
		{
			return nullptr;
		}


		std::shared_ptr<RigidBody> body = std::make_shared<RigidBody>(is_static, physics::Shape::CIRCLE, physics::Circle(radius), material, MassData(area * density));

		return body;
	}

	std::shared_ptr<RigidBody> RigidBody::CreateAABBRigidBody(bool is_static, float length, float width, float density,
		Material material)
	{
		float area = width * length;
		float mass = area * density;

		std::shared_ptr<RigidBody> body = std::make_shared<RigidBody>(is_static, physics::Shape::BOX, physics::AABB(length, width), material, MassData(area * density));

		return body;
	}
};
