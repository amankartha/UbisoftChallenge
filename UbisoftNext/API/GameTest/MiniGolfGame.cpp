#include "stdafx.h"
#include <Windows.h>

#include "MiniGolfGame.h"

#include "cameraManager.h"
#include "CursorGameObject.h"
#include "InputHandler.h"
#include "GameObjectManager.h"
#include "MiniGolfCameraGameObject.h"
#include "Renderer.h"

MiniGolfGame::MiniGolfGame()
{
	 
	/// Add Input to keep track of
	GetInputHandler()->SetKeysToTrack(std::vector<int>{VK_LBUTTON, VK_RIGHT, 'W', 'A', 'S', 'D'});
	///----------------------------------------------------------
	///----------------------------------------------------------
	///Add Gameobjects that dont need to belong to a scene
	GetGameObjectManager()->Create<CursorGameObject>("Cursor");
	GetGameObjectManager()->Create<MiniGolfCameraGameObject>("MiniGolfCamera");


	///--------------------------
}

MiniGolfGame::~MiniGolfGame()
{
}

void MiniGolfGame::InternalInit()
{
	Game::InternalInit();
	while (ShowCursor(FALSE) >= 0);

}

void MiniGolfGame::InternalUpdate(const float deltaTime)
{
	Game::InternalUpdate(deltaTime);
}

void MiniGolfGame::InternalRender()
{
	Game::InternalRender();
	GetRenderer()->DrawGridWithCamera(GetCameraManager()->GetMainCamera(), m_grid_system_);
	App::Print(100, 100, GetCameraManager()->GetMainCamera().GetPosition().Print().c_str());
}

void MiniGolfGame::InternalShutdown()
{
	
}

GRID::GridSystem MiniGolfGame::GetGrid()
{
	return m_grid_system_;
}
