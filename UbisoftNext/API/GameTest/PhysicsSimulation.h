#pragma once
#include <memory>

namespace physics
{
	class RigidBody;

	class PhysicsSimulation
	{
	public:
		PhysicsSimulation(float gravity = 9.8f,int MAX_RIGIDBODIES = 1000) : m_gravity(gravity) 
		{
			Init(MAX_RIGIDBODIES);
		}
		void AddBody(std::shared_ptr<RigidBody> rigid_body);
		void RemoveBody(std::shared_ptr<RigidBody> rigid_body);
		void Update();

		void Init(int rigidBodyCount);

	private:
		void ResolveCollision(RigidBody* A,RigidBody* B);

	private:
		//RigidBody m_bodies[];
		float m_gravity;
	};

};

