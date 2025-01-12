#include "stdafx.h"
#include "PhysicsSimulation.h"
#include "RigidBody.h"
namespace physics
{
	void PhysicsSimulation::AddBody(std::shared_ptr<RigidBody> rigid_body)
	{/*
		auto it = std::find(m_bodies.begin(), m_bodies.end(), rigid_body);
		if (it == m_bodies.end()) {
			m_bodies.push_back(rigid_body); 
		}*/

	}

	void PhysicsSimulation::RemoveBody(std::shared_ptr<RigidBody> rigid_body)
	{
		/*auto it = std::find(m_bodies.begin(), m_bodies.end(), rigid_body);
		if (it != m_bodies.end()) {
			m_bodies.erase(it); 
		}*/
	}

	void PhysicsSimulation::Init(int rigidBodyCount)
	{
		/*m_bodies = new RigidBody[rigidBodyCount];*/
	}
};
