#pragma once
#include <vector>

class Crigidbody;
namespace PHYSICS
{
	class PhysicsSimulation
	{
	private:
		std::vector<Crigidbody* > m_bodies;
		float m_gravity;

	public:
		PhysicsSimulation(float gravity) : m_gravity(gravity) 
		{
			m_bodies.reserve(150);
		}

		void AddBody(Crigidbody& m_bodies);
		void RemoveBody(Crigidbody& m_bodies);

		void Update();
	};

};

