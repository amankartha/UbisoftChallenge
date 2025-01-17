#include "stdafx.h"
#include "TestGame.h"

#include <windows.h> 
//------------------------------------------------------------------------
#include "appUtility.h"
#include <GameObject.h>
#include <CRenderer.h>


#include "BulletGameObject.h"
#include "Renderer.h"
#include "Scheduler.h"
#include "Ccamera.h"
#include "CPoolManager.h"
#include "Pathfinding.h"
#include "GameObjectManager.h"
#include "InputHandler.h"

int player;
int mouse;
int camera;
int CenterObject;

std::shared_ptr<Pathfinding> pathFinder;
std::vector<GRID::Cell*> pathToDraw;

void TestGame::InternalInit()
{
	Game::InternalInit();



	pathFinder = std::make_shared<Pathfinding>(m_gridSystem);
	/*m_gridSystem.SetObstacle(Vector2(1, 1));
	m_gridSystem.SetObstacle(Vector2(0, 1));
	m_gridSystem.SetObstacle(Vector2(1, 0));
	m_gridSystem.SetObstacle(Vector2(-1, -1));
	m_gridSystem.SetObstacle(Vector2(-1, 1));*/

	GetInputHandler()->SetKeysToTrack(std::vector<int>{'A', 'B', 'C'});

	OutputDebugStringW(L"My output string.");

	while (ShowCursor(FALSE) >= 0);  //Some code I found online that hides the cursor while its above the window.
	mouse = GetGameObjectManager()->Create<GameObject>("Mouse");
	player = GetGameObjectManager()->Create<GameObject>("Player");
	camera = GetGameObjectManager()->Create<GameObject>("Camera");
	CenterObject = GetGameObjectManager()->Create<GameObject>("Center");

	//m_renderer.SetShake(true);

	GetGameObjectManager()->Find(camera)->AddComponent<Ccamera>(GetCameraManager(),0);
	GetGameObjectManager()->Find(camera)->GetComponent<Ccamera>()->SetTransform(GetGameObjectManager()->Find(camera)->GetTransformComponent().GetTransform());
	
	GetCameraManager()->SetMainCamera(0);

	GetGameObjectManager()->Find(player)->AddComponent<CRenderer>(GetRenderer())->SetRendererOnOff(true);
	GetGameObjectManager()->Find(player)->GetComponent<CRenderer>()->SetSprite(*App::CreateSprite(".\\TestData\\Test.bmp", 8, 4));
	//GetGameObjectManager()->Find(player)->GetComponent<CRenderer>()->SetRenderLayer(RenderLayer::Default);
	GetGameObjectManager()->Find(player)->AddComponent<CPoolManager<BulletGameObject>> (this,100,this);


	GetGameObjectManager()->Find(mouse)->AddComponent<CRenderer>(GetRenderer(),RenderLayer::UI)->SetRendererOnOff(true);
	GetGameObjectManager()->Find(mouse)->GetComponent<CRenderer>()->SetSprite(*App::CreateSprite(".\\TestData\\cursor_pointerFlat.png", 1, 1));
	//GetGameObjectManager()->Find(mouse)->GetComponent<CRenderer>()->SetRenderLayer(RenderLayer::UI);


	GetGameObjectManager()->Find(CenterObject)->AddComponent<CRenderer>(GetRenderer())->SetRendererOnOff(true);
	GetGameObjectManager()->Find(CenterObject)->GetComponent<CRenderer>()->SetSprite(*App::CreateSprite(".\\TestData\\tile_grey.png", 1, 1));
	GetGameObjectManager()->Find(CenterObject)->GetComponent<Ctransform>()->SetScale(0.1f);



	GetGameObjectManager()->Find(player)->GetTransformComponent().OffsetPosition(Vector2(-APP_VIRTUAL_WIDTH/2, -APP_VIRTUAL_HEIGHT/2));
	GetGameObjectManager()->Find(CenterObject)->GetTransformComponent().OffsetPosition(Vector2(100, 100));

	GetGameObjectManager()->Find(mouse)->SetChild(GetGameObjectManager()->Find(player));

	GetGameObjectManager()->Find(player)->SetChild(GetGameObjectManager()->Find(CenterObject));
}

void TestGame::InternalUpdate(const float deltaTime)
{
	Game::InternalUpdate(deltaTime);


	


	GetGameObjectManager()->Find(mouse)->GetComponent<Ctransform>()->SetPosition(GetCameraManager()->GetMainCamera().GetPosition() + App::GetMousePosVec2());


	if (GetInputHandler()->IsKeyHeld('A'))
	{
		GetGameObjectManager()->Find(player)->GetComponent<CPoolManager<BulletGameObject>>()->Spawn();
		GetGameObjectManager()->Find(player)->GetComponent<CPoolManager<BulletGameObject>>()->Spawn();
		GetGameObjectManager()->Find(player)->GetComponent<CPoolManager<BulletGameObject>>()->Spawn();
		GetGameObjectManager()->Find(player)->GetComponent<CPoolManager<BulletGameObject>>()->Spawn();
		GetGameObjectManager()->Find(player)->GetComponent<CPoolManager<BulletGameObject>>()->Spawn();
		GetGameObjectManager()->Find(player)->GetComponent<CPoolManager<BulletGameObject>>()->Spawn();
		GetGameObjectManager()->Find(player)->GetComponent<CPoolManager<BulletGameObject>>()->Spawn();
		GetGameObjectManager()->Find(player)->GetComponent<CPoolManager<BulletGameObject>>()->Spawn();
		GetGameObjectManager()->Find(player)->GetComponent<CPoolManager<BulletGameObject>>()->Spawn();
		GetGameObjectManager()->Find(player)->GetComponent<CPoolManager<BulletGameObject>>()->Spawn();
		GetGameObjectManager()->Find(player)->GetComponent<CPoolManager<BulletGameObject>>()->Spawn();
		GetGameObjectManager()->Find(player)->GetComponent<CPoolManager<BulletGameObject>>()->Spawn();
		GetGameObjectManager()->Find(player)->GetComponent<CPoolManager<BulletGameObject>>()->Spawn();
		GetGameObjectManager()->Find(player)->GetComponent<CPoolManager<BulletGameObject>>()->Spawn();
		GetGameObjectManager()->Find(player)->GetComponent<CPoolManager<BulletGameObject>>()->Spawn();
		GetGameObjectManager()->Find(player)->GetComponent<CPoolManager<BulletGameObject>>()->Spawn();
		GetGameObjectManager()->Find(player)->GetComponent<CPoolManager<BulletGameObject>>()->Spawn();
		GetGameObjectManager()->Find(player)->GetComponent<CPoolManager<BulletGameObject>>()->Spawn();
		GetGameObjectManager()->Find(player)->GetComponent<CPoolManager<BulletGameObject>>()->Spawn();
		GetGameObjectManager()->Find(player)->GetComponent<CPoolManager<BulletGameObject>>()->Spawn();
		GetGameObjectManager()->Find(player)->GetComponent<CPoolManager<BulletGameObject>>()->Spawn();
		GetGameObjectManager()->Find(player)->GetComponent<CPoolManager<BulletGameObject>>()->Spawn();
		GetGameObjectManager()->Find(player)->GetComponent<CPoolManager<BulletGameObject>>()->Spawn();
		GetGameObjectManager()->Find(player)->GetComponent<CPoolManager<BulletGameObject>>()->Spawn();
		GetGameObjectManager()->Find(player)->GetComponent<CPoolManager<BulletGameObject>>()->Spawn();

	}

	if (GetInputHandler()->IsKeyPressed('B'))
	{
		GetGameObjectManager()->Find(player)->RemoveComponent<CPoolManager<BulletGameObject>>();
	}

	if (App::IsKeyPressed('N'))
	{
		GetGameObjectManager()->Find(CenterObject)->SetParent(GetGameObjectManager()->Find(player));
	}
	
}

void TestGame::InternalRender()
{

	Game::InternalRender();
	//GetRenderer()->RenderAll(GetCameraManager()->GetMainCamera());

	//App::Print(100, 700,GetInputHandler()->GetCurrentString().c_str());
	App::Print(100, 600, std::to_string(GetGameObjectManager()->Find(player)->GetComponent<CPoolManager<BulletGameObject>>()->GetObjectPoolSize()).c_str());
	App::Print(100, 300, std::to_string(GetGameObjectManager()->Find(player)->GetComponent<CPoolManager<BulletGameObject>>()->GetObjectPoolSize()).c_str());
	//App::Print(100, 500,std::to_string(GetGameObjectManager()->GetNumberOfGameObjects()).c_str());
	


	//App::Print(200, 500, CenterObject->m_parent->m_name.c_str());
	App::Print(200, 200, GetGameObjectManager()->Find(CenterObject)->GetTransformComponent().GetWorldPosition().Print().c_str());
	//App::Print(100,100,App::ScreenToWorld(m_cameraManager.GetMainCamera(), App::GetMousePosVec2()).Print().c_str());
}

void TestGame::InternalShutdown()
{

}
