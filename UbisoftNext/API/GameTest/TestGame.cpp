#include "stdafx.h"
#include "TestGame.h"

#include <windows.h> 
#include <math.h>  
//------------------------------------------------------------------------
#include "appUtility.h"
#include <GameObject.h>
#include <CRenderer.h>
#include "Renderer.h"
#include "Scheduler.h"
#include "Ccamera.h"
#include "Pathfinding.h"
CSimpleSprite* testSprite;
GameObject* player;
GameObject* mouse;
GameObject* camera;
GameObject* CenterObject;

std::shared_ptr<Pathfinding> pathFinder;
std::vector<GRID::Cell*> pathToDraw;


void TestGame::InternalInit()
{
	Game::InternalInit();
	m_gameObjectManager.InitAll();

	pathFinder = std::make_shared<Pathfinding>(m_gridSystem);
	/*m_gridSystem.SetObstacle(Vector2(1, 1));
	m_gridSystem.SetObstacle(Vector2(0, 1));
	m_gridSystem.SetObstacle(Vector2(1, 0));
	m_gridSystem.SetObstacle(Vector2(-1, -1));
	m_gridSystem.SetObstacle(Vector2(-1, 1));*/


	OutputDebugStringW(L"My output string.");

	while (ShowCursor(FALSE) >= 0);  //Some code I found online that hides the cursor while its above the window.
	mouse = &m_gameObjectManager.Create("Mouse");
	player = &m_gameObjectManager.Create("Player");
	camera = &m_gameObjectManager.Create("Camera");
	CenterObject = &m_gameObjectManager.Create("Center");
	scheduler = new Scheduler();

	//m_renderer.SetShake(true);

	camera->AddComponent<Ccamera>(m_cameraManager,0);
	camera->GetComponent<Ccamera>()->SetTransform(camera->GetTransformComponent().GetTransform());
	
	m_cameraManager.SetMainCamera(0);

	player->AddComponent<CRenderer>(m_renderer)->CreateSprite(".\\TestData\\Test.bmp", 8, 4);
	player->GetComponent<CRenderer>()->SetRenderLayer(RenderLayer::Default);


	mouse->AddComponent<CRenderer>(m_renderer);
	mouse->GetComponent<CRenderer>()->CreateSprite(".\\TestData\\cursor_pointerFlat.png", 1, 1);
	mouse->GetComponent<CRenderer>()->SetRenderLayer(RenderLayer::UI);


	CenterObject->AddComponent<CRenderer>(m_renderer);
	CenterObject->GetComponent<CRenderer>()->CreateSprite(".\\TestData\\tile_grey.png", 1, 1);
	CenterObject->GetComponent<Ctransform>()->SetScale(0.1f);



	player->GetTransformComponent().OffsetPosition(Vector2(1, 1));
	CenterObject->GetTransformComponent().OffsetPosition(Vector2(100, 100));

	mouse->SetChild(player);

	player->SetChild(CenterObject);
}

void TestGame::InternalUpdate(const float deltaTime)
{
	scheduler->Update();
	mouse->GetComponent<Ctransform>()->SetPosition(App::ScreenToWorld(m_cameraManager.GetMainCamera(),App::GetMousePosVec2()));


	m_gameObjectManager.UpdateAll();
}

void TestGame::InternalRender()
{

	Game::InternalRender();
	m_renderer.RenderAll(m_cameraManager.GetMainCamera());

	testSprite = App::CreateSprite(".\\TestData\\Test.bmp", 8, 4);
	for (int i = 0; i < 15000; ++i)
	{
		testSprite->SetPositionWithOffset(20, 20);
		testSprite->Draw();
	}
	
	App::Print(200, 500, CenterObject->m_parent->m_name.c_str());
	App::Print(200, 200, CenterObject->GetTransformComponent().GetWorldPosition().Print().c_str());
	App::Print(100,100,App::ScreenToWorld(m_cameraManager.GetMainCamera(), App::GetMousePosVec2()).Print().c_str());
}

void TestGame::InternalShutdown()
{
	delete testSprite;
	delete scheduler;
	
}
