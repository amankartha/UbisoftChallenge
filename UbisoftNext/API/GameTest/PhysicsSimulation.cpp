#include "stdafx.h"
#include "PhysicsSimulation.h"
#include "RigidBody.h"
#include "Collider.h"




void physics::PhysicsSimulation::ResolveCollision(RigidBody* A, RigidBody* B)
{
	//// Calculate relative velocity

	//Vector2 rv = B->m_velocity - A->m_velocity;

	//// Calculate relative velocity in terms of the normal direction

	//float velAlongNormal = Vector2::Dot(rv, normal);

	//// Do not resolve if velocities are separating


	//if (velAlongNormal > 0) return;

	//// Calculate restitution

	//float e = (std::min)(A->GetBounciness(),B->GetBounciness());

	//// Calculate impulse scalar

	//float j = -(1 + e) * velAlongNormal;

	//j /= 1 / A->GetMass() + 1 / B->GetMass();

	//// Apply impulse

	//Vector2 impulse = j * normal;

	//A->m_velocity = (A->m_velocity) - (A->GetInverseMass() * impulse);

	//B->m_velocity = (B->m_velocity) + (A->GetInverseMass() * impulse);

}

void physics::PhysicsSimulation::BroadPhasePairGeneration()
{
	m_pairs.clear();

	Collider A();
	Collider B();

	

}
