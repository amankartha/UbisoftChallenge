#include "stdafx.h"
#include "PhysicsSimulation.h"
#include "RigidBody.h"
namespace physics
{
	

	int PhysicsSimulation::AddBody(Shape rigidBodyShape)
	{
		return m_rigidbody_pool_.Get()->m_index;
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
		m_rigidbody_pool_.InitializePool(rigidBodyCount);
	}
};
