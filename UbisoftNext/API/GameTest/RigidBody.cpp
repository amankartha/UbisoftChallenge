#include "stdafx.h"
#include "RigidBody.h"

bool RigidBody::CreateCircleRigidBody(bool is_static, float radius, float density, Material material)
{
	float area = PI * radius * radius;

	if (area < MIN_BODY_SIZE)
	{
		return false;
	}
	return true;
}
