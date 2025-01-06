#pragma once
#include "stdafx.h"
#include "RigidBody.h"
#include "Collider.h"


namespace physics
{
	struct Collision
	{
		RigidBody* A;
		RigidBody* B;
		float penetration;
		Vector2 normal;
	};

	/*struct Pair
	{
		RigidBody* A;
		RigidBody* B;

		Pair(RigidBodyA* A,)
	};*/

	bool CircleVsCircle(Collision* collision)
	{
		RigidBody* A = collision->A;
		RigidBody* B = collision->B;

		Vector2 direction = B->GetPosition() - A->GetPosition();


	}

};
