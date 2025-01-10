#pragma once
#include <vector>
#include <memory>

class RigidBody;

namespace physics
{
	class PhysicsSimulation
	{
	public:
		PhysicsSimulation(float gravity = 9.8f) : m_gravity(gravity) 
		{
			m_bodies.reserve(150);
		}
		void AddBody(std::shared_ptr<RigidBody> rigid_body);
		void RemoveBody(std::shared_ptr<RigidBody> rigid_body);
		void Update();

	private:
		void ResolveCollision(RigidBody* A,RigidBody* B);

	private:
		std::vector<std::shared_ptr<RigidBody>> m_bodies;
		float m_gravity;
	};

};

