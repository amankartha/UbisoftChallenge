#include "stdafx.h"
#include "Game.h"

#include "Ccamera.h"
#include "GameObjectManager.h"
#include "InputHandler.h"
#include "PhysicsSimulation.h"
#include "Renderer.h"
#include "Scheduler.h"


Game::Game()
	: m_gameObjectManager(std::make_unique<GameObjectManager>(this)),  // Initialize with new instances
	m_renderer(std::make_unique<Renderer>()),
	m_cameraManager(std::make_unique<CameraManager>()),
	m_scheduler(std::make_unique<Scheduler>()),
	m_physicsSimulation(std::make_unique<physics::PhysicsSimulation>(this)),
	m_input_handler(std::make_unique<InputHandler>())
{
	// You can initialize other members here if needed
}

Game::~Game(){}  //need this for unique ptrs to work because it needs a place to call its delete

void Game::InternalInit()
{
	/*auto GO = m_gameObjectManager.Create("MAINCAMERA");
	GO.AddComponent<Ccamera>(m_cameraManager,0);

	auto camera = m_cameraManager.CreateCamera(0);
	*/
}

void Game::InternalUpdate(const float deltaTime)
{
	m_input_handler->Update();
	m_input_handler->PollInputs();
	m_scheduler->Update();
}

void Game::InternalRender()
{
	
}

Renderer* Game::GetRenderer() const
{
	return m_renderer.get();
}

GameObjectManager* Game::GetGameObjectManager() const
{
	return m_gameObjectManager.get();
}

CameraManager* Game::GetCameraManager() const
{
	return m_cameraManager.get();
}

Scheduler* Game::GetScheduler() const
{
	return m_scheduler.get();
}

physics::PhysicsSimulation* Game::GetPhysicsSimulation() const
{
	return m_physicsSimulation.get();
}

InputHandler* Game::GetInputHandler()
{
	return m_input_handler.get();
}
