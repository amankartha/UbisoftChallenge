#pragma once
#include <memory>
#include "PhysicsSimulation.h"
#include "Renderer.h"
#include "CameraManager.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "Scheduler.h"
class Game
{
protected:
	
	GameObjectManager m_gameObjectManager;
	Renderer m_renderer;
	CameraManager m_cameraManager;
	Scheduler* scheduler;
	PHYSICS::PhysicsSimulation m_physicsSimulation;
public:
	
	~Game() {}

	virtual void InternalInit();
	virtual	void InternalUpdate(const float deltaTime) = 0;
	virtual void InternalRender();
	virtual void InteralShutdown() = 0;

protected:
	

	
	
};

