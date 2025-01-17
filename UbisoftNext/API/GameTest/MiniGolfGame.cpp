#include "stdafx.h"
#include <Windows.h>

#include "MiniGolfGame.h"

#include "CursorGameObject.h"
#include "InputHandler.h"
#include "GameObjectManager.h"

MiniGolfGame::MiniGolfGame()
{
}

MiniGolfGame::~MiniGolfGame()
{
}

void MiniGolfGame::InternalInit()
{
	Game::InternalInit();

	while (ShowCursor(FALSE) >= 0);  //Some code I found online that hides the cursor while its above the window.
	/// Add Input to keep track of
	GetInputHandler()->SetKeysToTrack(std::vector<int>{VK_LBUTTON, VK_RIGHT});
	///----------------------------------------------------------
	///----------------------------------------------------------
	///Add Gameobjects that dont need to belong to a scene
	GetGameObjectManager()->Create<CursorGameObject>("Cursor");
	///--------------------------
}

void MiniGolfGame::InternalUpdate(const float deltaTime)
{
	Game::InternalUpdate(deltaTime);
}

void MiniGolfGame::InternalRender()
{
	Game::InternalRender();
}

void MiniGolfGame::InternalShutdown()
{
	
}

GRID::GridSystem MiniGolfGame::GetGrid()
{
	return m_grid_system_;
}
