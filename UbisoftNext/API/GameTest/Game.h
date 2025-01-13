#pragma once
#include "PhysicsSimulation.h"
#include "Renderer.h"
#include "CameraManager.h"
#include "GameObjectManager.h"
#include "InputHandler.h"
#include "Scheduler.h"
class Game
{
protected:
	GameObjectManager m_gameObjectManager;
	Renderer m_renderer;
	CameraManager m_cameraManager;
	Scheduler* m_scheduler;
	physics::PhysicsSimulation m_physicsSimulation;
	InputHandler m_input_handler;
public:

	Game() : m_gameObjectManager(this) {}

	~Game() = default;

	virtual void InternalInit();
	virtual	void InternalUpdate(const float deltaTime);
	virtual void InternalRender();
	virtual void InternalShutdown() = 0;

protected:
	

	
	
};

