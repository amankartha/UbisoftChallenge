#pragma once
#include "PhysicsSimulation.h"
#include <memory>
class Game
{
private:
	std::unique_ptr<PHYSICS::PhysicsSimulation> m_physicsSimulation;
	
public:
	Game() 
	{
		m_physicsSimulation = std::make_unique<PHYSICS::PhysicsSimulation>(9.81f);
	}
	~Game() {}

	virtual void Init() = 0;
	virtual	void Update(const float deltaTime) = 0;
	virtual void Render() = 0;
	virtual void Shutdown() = 0;

};

