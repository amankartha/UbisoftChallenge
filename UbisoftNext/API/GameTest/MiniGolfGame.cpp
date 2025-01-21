#include "stdafx.h"
#include <Windows.h>

#include "MiniGolfGame.h"

#include "BackGroundArtGameObject.h"
#include "BoostPadGameObject.h"
#include "BoundaryGameObject.h"
#include "cameraManager.h"
#include "CCameraController.h"
#include "CGameManager.h"
#include "CRenderer.h"
#include "Crigidbody.h"
#include "CursorGameObject.h"
#include "MiniGolfGameManagerGameObject.h"
#include "InputHandler.h"
#include "GameObjectManager.h"
#include "GolfBallGameObject.h"
#include "MiniGolfCameraGameObject.h"
#include "PhysicsSimulation.h"
#include "Renderer.h"

int golfBallID;
int camId;

MiniGolfGame::MiniGolfGame()
{
	
}

MiniGolfGame::~MiniGolfGame()
{
}

void MiniGolfGame::InternalInit()
{
	Game::InternalInit();

	

	while (ShowCursor(FALSE) >= 0);

	/// Add Input to keep track of
	GetInputHandler()->SetKeysToTrack(std::vector<int>{VK_LBUTTON, VK_RBUTTON, 'W', 'A', 'S', 'D', 'F'});
	///----------------------------------------------------------
	///----------------------------------------------------------
	///Add Gameobjects that dont need to belong to a scene
	GetGameObjectManager()->AddToLookupTable("Cursor", GetGameObjectManager()->Create<CursorGameObject>("Cursor"));

	GetGameObjectManager()->CreateAndAddToLookUpTable<MiniGolfCameraGameObject>("MiniGolfCamera");

	int managerid = GetGameObjectManager()->CreateAndAddToLookUpTable<MiniGolfGameManagerGameObject>("GameManager",2);

	//Game Boundaries  //todo: this can be its own gameobject prefab
    GetGameObjectManager()->Create<BoundaryGameObject>("BoundaryNorth",Vector2(0,900),4000,100);
    GetGameObjectManager()->Create<BoundaryGameObject>("BoundarySouth",Vector2(0,-900),4000,100);
    GetGameObjectManager()->Create<BoundaryGameObject>("BoundaryWest",Vector2(-2000,0),100,2800);
    GetGameObjectManager()->Create<BoundaryGameObject>("BoundaryEast",Vector2(2000,0),100,2800);




	//GetGameObjectManager()->FindUsingTable("MiniGolfCamera")->GetComponent<CCameraController>()->SetTransformToFollow(
	//	GetGameObjectManager()->Find(GetGameObjectManager()->SearchTable("GolfBall"))->GetComponent<Ctransform>()
	//	);

	int id = GetGameObjectManager()->Create<BackGroundArtGameObject>("Background");
	GetGameObjectManager()->Find(id)->GetComponent<CRenderer>()->SetTiled(IntVector2(10, 5));
//	GetGameObjectManager()->Create<BoostPadGameObject>("BoostPad");

	///--------------------------
	
	GetGameObjectManager()->Find(managerid)->GetComponent<CGameManager>()->StartGame();
	
}

void MiniGolfGame::InternalUpdate(const float deltaTime)
{
	Game::InternalUpdate(deltaTime);
	
}

void MiniGolfGame::InternalRender()
{
	
	Game::InternalRender();
	//GetRenderer()->DrawGridWithCamera(GetCameraManager()->GetMainCamera(), m_grid_system_);
	//GetRenderer()->DrawFilledCells (m_grid_system_);
	GetPhysicsSimulation()->DrawColliders();
	

}

void MiniGolfGame::InternalShutdown()
{
	
}

GRID::GridSystem* MiniGolfGame::GetGridSystem() 
{
	return &m_grid_system_;
}
