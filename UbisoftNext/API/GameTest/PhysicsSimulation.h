#pragma once
#include <memory>

#include "ObjectPool.h"
#include "RigidBody.h"
namespace physics
{
	enum class Shape;
}

namespace physics
{
	

	class PhysicsSimulation
	{
	public:
		PhysicsSimulation(Game* instance,float gravity = 9.8f,int MAX_RIGIDBODIES = 1000) : m_gravity(gravity),m_rigidbody_pool_(instance,MAX_RIGIDBODIES)
		{
			Init(MAX_RIGIDBODIES);
		}
		RigidBody* AddBody(Shape rigidBodyShape);
		void RemoveBody(std::shared_ptr<RigidBody> rigid_body);
		void Update();

		void Init(int rigidBodyCount);

	private:
		void ResolveCollision(RigidBody* A,RigidBody* B);

	private:
		float m_gravity;
		ObjectPool<RigidBody> m_rigidbody_pool_;
	};

};

