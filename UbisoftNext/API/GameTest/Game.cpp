#include "stdafx.h"
#include "Game.h"

void Game::InternalInit()
{
	

	auto camera = m_cameraManager.CreateCamera(0);
}

void Game::InternalRender()
{
	m_renderer.RenderAll(m_cameraManager.GetMainCamera());
}
