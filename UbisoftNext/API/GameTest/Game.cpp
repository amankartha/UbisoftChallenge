#include "stdafx.h"
#include "Game.h"

#include "Ccamera.h"

void Game::InternalInit()
{
	/*auto GO = m_gameObjectManager.Create("MAINCAMERA");
	GO.AddComponent<Ccamera>(m_cameraManager,0);

	auto camera = m_cameraManager.CreateCamera(0);
	*/
}

void Game::InternalUpdate(const float deltaTime)
{
	m_input_handler.Update();
	m_input_handler.PollInputs();
	m_scheduler->Update();
}

void Game::InternalRender()
{
	
}
