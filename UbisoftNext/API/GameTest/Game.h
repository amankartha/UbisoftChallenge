#pragma once
#include "PhysicsSimulation.h"
#include "Renderer.h"
#include "CameraManager.h"
#include "GameObjectManager.h"
#include "Scheduler.h"
class Game
{
protected:
	GameObjectManager m_gameObjectManager;
	Renderer m_renderer;
	CameraManager m_cameraManager;
	Scheduler* scheduler;
	physics::PhysicsSimulation m_physicsSimulation;
public:
	
	~Game() = default;

	virtual void InternalInit();
	virtual	void InternalUpdate(const float deltaTime) = 0;
	virtual void InternalRender();
	virtual void InternalShutdown() = 0;

protected:
	

	
	
};

