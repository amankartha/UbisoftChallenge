#include "stdafx.h"
#include "Game.h"

void Game::InternalInit()
{
	m_gameObjectMap.reserve(5000);

	auto camera = m_cameraManager.CreateCamera(0);
}

void Game::InternalRender()
{
	m_renderer.RenderAll(m_cameraManager.GetMainCamera().GetTransform(),m_cameraManager.GetMainCamera().GetZoom());
}
