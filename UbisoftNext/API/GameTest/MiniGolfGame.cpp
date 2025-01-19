#include "stdafx.h"
#include <Windows.h>

#include "MiniGolfGame.h"

#include "cameraManager.h"
#include "Crigidbody.h"
#include "CursorGameObject.h"
#include "GameManager.h"
#include "InputHandler.h"
#include "GameObjectManager.h"
#include "GolfBallGameObject.h"
#include "MiniGolfCameraGameObject.h"
#include "PhysicsSimulation.h"
#include "Renderer.h"

int GameManagerID;
int golfBallID;
MiniGolfGame::MiniGolfGame()
{
	 
	/// Add Input to keep track of
	GetInputHandler()->SetKeysToTrack(std::vector<int>{VK_LBUTTON, VK_RBUTTON, 'W', 'A', 'S', 'D', 'F', 'T','L' });
	///----------------------------------------------------------
	///----------------------------------------------------------
	///Add Gameobjects that dont need to belong to a scene
	GetGameObjectManager()->Create<CursorGameObject>("Cursor");
	GetGameObjectManager()->Create<MiniGolfCameraGameObject>("MiniGolfCamera");
	GameManagerID =  GetGameObjectManager()->Create<GameManager>("GameManager");
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
	if (App::IsKeyPressed('B'))
	{
		GetGridSystem()->isFound = false;
	}
	if (App::IsKeyPressed('P'))
	{
		int id = GetGameObjectManager()->Create<GameObject>("testRigidbody");
		GetGameObjectManager()->Find(id)->AddComponent<Crigidbody>(GetPhysicsSimulation(), 15.0f, 0.3f,0.4f, false);
		GetGameObjectManager()->Find(id)->GetTransformComponent().SetPosition(Vector2(FRAND_RANGE(-400, 400), FRAND_RANGE(-400, 400)));
	}
	if (GetInputHandler()->IsKeyPressed('L'))
	{
		int id = GetGameObjectManager()->Create<GameObject>("testRigidbody");
		GetGameObjectManager()->Find(id)->AddComponent<Crigidbody>(GetPhysicsSimulation(), 30.0f,30.0f, 0.3f,0.4 ,true);
		GetGameObjectManager()->Find(id)->GetTransformComponent().SetPosition(Vector2(FRAND_RANGE(-400, 400), FRAND_RANGE(-400, 400)));
	}
}

void MiniGolfGame::InternalRender()
{
	Game::InternalRender();
	GetRenderer()->DrawGridWithCamera(GetCameraManager()->GetMainCamera(), m_grid_system_);
	GetRenderer()->DrawFilledCells(m_grid_system_);
	GetPhysicsSimulation()->DrawColliders();
	if (GetGridSystem()->isFound)
	{
		App::Print(500, 500, "FOUNDDDDDDDDD");
	}
	
	
	//App::Print(100, 100, GetRenderer()->.GetPosition().Print().c_str());
	//App::Print(300, 100, std::to_string(GetGameObjectManager()->GetNumberOfGameObjects()).c_str());
}

void MiniGolfGame::InternalShutdown()
{
	
}

GRID::GridSystem* MiniGolfGame::GetGridSystem() 
{
	return &m_grid_system_;
}
