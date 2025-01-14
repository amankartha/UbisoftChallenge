#include "stdafx.h"
#include "TestGame.h"

#include <windows.h> 
//------------------------------------------------------------------------
#include "appUtility.h"
#include <GameObject.h>
#include <CRenderer.h>
#include "Renderer.h"
#include "Scheduler.h"
#include "Ccamera.h"
#include "Pathfinding.h"
#include "GameObjectManager.h"
#include "InputHandler.h"


GameObject* player;
GameObject* mouse;
GameObject* camera;
GameObject* CenterObject;

std::shared_ptr<Pathfinding> pathFinder;
std::vector<GRID::Cell*> pathToDraw;

void TestGame::InternalInit()
{
	Game::InternalInit();
	GetGameObjectManager()->InitAll();

	pathFinder = std::make_shared<Pathfinding>(m_gridSystem);
	/*m_gridSystem.SetObstacle(Vector2(1, 1));
	m_gridSystem.SetObstacle(Vector2(0, 1));
	m_gridSystem.SetObstacle(Vector2(1, 0));
	m_gridSystem.SetObstacle(Vector2(-1, -1));
	m_gridSystem.SetObstacle(Vector2(-1, 1));*/



	OutputDebugStringW(L"My output string.");

	while (ShowCursor(FALSE) >= 0);  //Some code I found online that hides the cursor while its above the window.
	mouse = &GetGameObjectManager()->Create("Mouse");
	player = &GetGameObjectManager()->Create("Player");
	camera = &GetGameObjectManager()->Create("Camera");
	CenterObject = &GetGameObjectManager()->Create("Center");

	//m_renderer.SetShake(true);

	camera->AddComponent<Ccamera>(GetCameraManager(),0);
	camera->GetComponent<Ccamera>()->SetTransform(camera->GetTransformComponent().GetTransform());
	
	GetCameraManager()->SetMainCamera(0);

	player->AddComponent<CRenderer>(GetRenderer())->CreateSprite(".\\TestData\\Test.bmp", 8, 4);
	player->GetComponent<CRenderer>()->SetRenderLayer(RenderLayer::Default);


	mouse->AddComponent<CRenderer>(GetRenderer());
	mouse->GetComponent<CRenderer>()->CreateSprite(".\\TestData\\cursor_pointerFlat.png", 1, 1);
	mouse->GetComponent<CRenderer>()->SetRenderLayer(RenderLayer::UI);


	CenterObject->AddComponent<CRenderer>(GetRenderer());
	CenterObject->GetComponent<CRenderer>()->CreateSprite(".\\TestData\\tile_grey.png", 1, 1);
	CenterObject->GetComponent<Ctransform>()->SetScale(0.1f);



	player->GetTransformComponent().OffsetPosition(Vector2(-APP_VIRTUAL_WIDTH/2, -APP_VIRTUAL_HEIGHT/2));
	CenterObject->GetTransformComponent().OffsetPosition(Vector2(100, 100));

	mouse->SetChild(player);

	player->SetChild(CenterObject);
}

void TestGame::InternalUpdate(const float deltaTime)
{
	Game::InternalUpdate(deltaTime);


	GetInputHandler()->SetKeysToTrack(std::vector<int>{'A','B','C'});


	mouse->GetComponent<Ctransform>()->SetPosition(GetCameraManager()->GetMainCamera().GetPosition() + App::GetMousePosVec2());


	if (GetInputHandler()->IsKeyHeld('A'))
	{
		CenterObject->RemoveParent();
	}

	if (GetInputHandler()->IsKeyPressed('B'))
	{
		for (int i = 0; i < 100; ++i)
		{
			GetGameObjectManager()-> Create("");
		}
	}

	if (App::IsKeyPressed('N'))
	{
		CenterObject->SetParent(player);
	}

	GetGameObjectManager()->UpdateAll();
}

void TestGame::InternalRender()
{

	Game::InternalRender();
	GetRenderer()->RenderAll(GetCameraManager()->GetMainCamera());

	App::Print(100, 700,GetInputHandler()->GetCurrentString().c_str());
	App::Print(100, 600,GetInputHandler()->GetBufferString().c_str());
	App::Print(100, 500,std::to_string(GetGameObjectManager()->GetNumberOfGameObjects()).c_str());
	


	//App::Print(200, 500, CenterObject->m_parent->m_name.c_str());
	App::Print(200, 200, CenterObject->GetTransformComponent().GetWorldPosition().Print().c_str());
	//App::Print(100,100,App::ScreenToWorld(m_cameraManager.GetMainCamera(), App::GetMousePosVec2()).Print().c_str());
}

void TestGame::InternalShutdown()
{

}
