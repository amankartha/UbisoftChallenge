#pragma once
#include <vector>
#include <memory>

struct Pair;
class RigidBody;

namespace physics
{
	class PhysicsSimulation
	{
	private:
		std::vector<std::unique_ptr<RigidBody>> m_bodies;
		std::vector<Pair> m_pairs;
		float m_gravity;

	public:
		PhysicsSimulation(float gravity = 9.8f) : m_gravity(gravity) 
		{
			m_bodies.reserve(150);
		}

		RigidBody* AddBody(RigidBody& m_bodies);
		void RemoveBody(RigidBody& m_bodies);

		
		
		void Update();

	private:
		void ResolveCollision(RigidBody* A,RigidBody* B);

		void BroadPhasePairGeneration();
	};

};

