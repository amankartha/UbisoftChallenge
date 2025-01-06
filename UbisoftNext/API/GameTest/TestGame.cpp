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
enum
{
	ANIM_FORWARDS,
	ANIM_BACKWARDS,
	ANIM_LEFT,
	ANIM_RIGHT,
};



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

	
	camera->AddComponent<Ccamera>(m_cameraManager);
	


	mouse->AddComponent<CRenderer>(m_renderer);
	mouse->GetComponent<CRenderer>()->CreateSprite(".\\TestData\\cursor_pointerFlat.png", 1, 1);
	mouse->GetComponent<CRenderer>()->SetRenderLayer(RenderLayer::UI);



	CenterObject->AddComponent<CRenderer>(m_renderer);
	CenterObject->GetComponent<CRenderer>()->CreateSprite(".\\TestData\\tile_grey.png", 1, 1);
	CenterObject->GetComponent<Ctransform>()->SetScale(0.1f);
	


	player->AddComponent<CRenderer>(m_renderer);
	player->GetComponent<CRenderer>()->CreateSprite(".\\TestData\\Test.bmp", 8, 4);


	//------------------------------------------------------------------------
	// Example Sprite Code....
	testSprite = App::CreateSprite(".\\TestData\\Test.bmp", 8, 4);
	testSprite->SetPosition(APP_VIRTUAL_WIDTH/2, APP_VIRTUAL_HEIGHT/2);
	const float speed = 1.0f / 15.0f;
	testSprite->CreateAnimation(ANIM_BACKWARDS, speed, { 0,1,2,3,4,5,6,7 });
	testSprite->CreateAnimation(ANIM_LEFT, speed, { 8,9,10,11,12,13,14,15 });
	testSprite->CreateAnimation(ANIM_RIGHT, speed, { 16,17,18,19,20,21,22,23 });
	testSprite->CreateAnimation(ANIM_FORWARDS, speed, { 24,25,26,27,28,29,30,31 });
	testSprite->SetScale(1.0f);
	//------------------------------------------------------------------------
}

void TestGame::InternalUpdate(const float deltaTime)
{
	scheduler->Update();
	mouse->GetComponent<Ctransform>()->SetPosition(App::GetMousePosVec2());


	//------------------------------------------------------------------------
	// Example Sprite Code....
	testSprite->Update(deltaTime);
	/*if (App::GetController().GetLeftThumbStickX() > 0.5f)
	{
		testSprite->SetAnimation(ANIM_RIGHT);
		float x, y;
		testSprite->GetPosition(x, y);
		x += 1.0f;
		testSprite->SetPosition(x, y);
	}*/

	if (App::IsKeyPressed(VK_RIGHT))
	{
		/*	testSprite->SetAnimation(ANIM_RIGHT);
			float x, y;
			testSprite->GetPosition(x, y);
			x += 1.0f;
			testSprite->SetPosition(x, y);*/
	//	player->GetComponent<Ctransform>()->OffsetPosition(Vector2::RIGHT);
		
	}
	if (App::IsKeyPressed(MK_LBUTTON))
	{
		pathToDraw = pathFinder->FindPath(Vector2(0, 0), (App::GetMousePosVec2() - Vector2(APP_VIRTUAL_WIDTH / 2, APP_VIRTUAL_HEIGHT / 2)) + m_cameraManager.GetMainCamera().GetPosition());
	}

	if (App::IsKeyPressed(MK_RBUTTON))
	{
		m_gridSystem.SetObstacle((App::GetMousePosVec2() - Vector2(APP_VIRTUAL_WIDTH / 2, APP_VIRTUAL_HEIGHT / 2)) + m_cameraManager.GetMainCamera().GetPosition());
	}
	if (App::IsKeyPressed(VK_UP))
	{
		/*auto g = Create("Generated");
		g->AddComponent<CRenderer>(m_renderer);
		g->GetComponent<CRenderer>()->CreateSprite(".\\TestData\\Test.bmp", 8, 4);
		

		g->GetTransform()->SetPosition(Vector2(FRAND_RANGE(0, APP_VIRTUAL_WIDTH), FRAND_RANGE(0, APP_VIRTUAL_WIDTH)));
		scheduler->AddTask([this]() { m_renderer.SetShakeOff(); }, 1500);*/
	}
	if (App::IsKeyPressed(VK_DOWN))
	{
		
	}
	if (App::IsKeyPressed(VK_LEFT))
	{
		/*testSprite->SetAnimation(ANIM_LEFT);
		float x, y;
		testSprite->GetPosition(x, y);
		x -= 1.0f;
		testSprite->SetPosition(x, y);*/
	//	player->GetComponent<Ctransform>()->OffsetPosition(Vector2::LEFT);
	}
	if (App::GetController().GetLeftThumbStickY() > 0.5f)
	{
		testSprite->SetAnimation(ANIM_FORWARDS);
		float x, y;
		testSprite->GetPosition(x, y);
		y += 1.0f;
		testSprite->SetPosition(x, y);
	}
	if (App::GetController().GetLeftThumbStickY() < -0.5f)
	{
		testSprite->SetAnimation(ANIM_BACKWARDS);
		float x, y;
		testSprite->GetPosition(x, y);
		y -= 1.0f;
		testSprite->SetPosition(x, y);
	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_UP, false))
	{
		testSprite->SetScale(testSprite->GetScale() + 0.1f);
	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_DOWN, false))
	{
		testSprite->SetScale(testSprite->GetScale() - 0.1f);
	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_LEFT, false))
	{
		testSprite->SetAngle(testSprite->GetAngle() + 0.1f);
	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_RIGHT, false))
	{
		testSprite->SetAngle(testSprite->GetAngle() - 0.1f);
	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_A, true))
	{
		testSprite->SetAnimation(-1);
	}
	//------------------------------------------------------------------------
	// Sample Sound.
	//------------------------------------------------------------------------
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_B, true))
	{
		App::PlaySound(".\\TestData\\Test.wav", true);
	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_X, true))
	{
		App::StopSound(".\\TestData\\Test.wav");
	}

	m_gameObjectManager.UpdateAll();
}

void TestGame::InternalRender()
{

	Game::InternalRender();
	//------------------------------------------------------------------------
	// Example Sprite Code....
	//testSprite->Draw();
	//------------------------------------------------------------------------

	//------------------------------------------------------------------------
	// Example Text.
	//------------------------------------------------------------------------
	//App::Print(100, 100, "Sample Text");
	



	//------------------------------------------------------------------------
	// Example Line Drawing.
	//------------------------------------------------------------------------
	/*static float a = 0.0f;
	const float r = 1.0f;
	float g = 1.0f;
	float b = 1.0f;
	a += 0.1f;
	for (int i = 0; i < 20; i++)
	{

		const float sx = -200 + sinf(a + i * 0.1f) * 60.0f;

		const float sy = -200 + cosf(a + i * 0.1f) * 60.0f;
		const float ex = 7000 - sinf(a + i * 0.1f) * 60.0f;
		const float ey = 7000 - cosf(a + i * 0.1f) * 60.0f;
		g = (float)i / 20.0f;
		b = (float)i / 20.0f;
		App::DrawLine(sx, sy, ex, ey, r, g, b);
	}*/
	//m_renderer.DrawGridWithCamera(m_cameraManager.GetMainCamera(), m_gridSystem);

	//if (pathToDraw.empty() || pathToDraw.size() < 2) {
	//	return; // No path to draw, exit the function
	//}

	//for (int i = 0; i < pathToDraw.size()-1; i++)
	//{
	//	Vector2 relativePos = m_gridSystem.GridToWorld(pathToDraw[i]->m_gridPosition) - m_cameraManager.GetMainCamera().GetPosition() + Vector2(APP_VIRTUAL_WIDTH / 2, APP_VIRTUAL_HEIGHT / 2);
	//	Vector2 relativePos2 = m_gridSystem.GridToWorld(pathToDraw[i+1]->m_gridPosition) - m_cameraManager.GetMainCamera().GetPosition() + Vector2(APP_VIRTUAL_WIDTH / 2, APP_VIRTUAL_HEIGHT / 2);
	//	App::DrawLine(relativePos.x, relativePos.y, relativePos2.x, relativePos2.y);
	//	//App::Print(100, 100 + i * 20, pathToDraw[i]->m_gridPosition.Print().c_str());
	//	//App::Print(100, 100 + i * 20, pathToDraw[i+1]->m_gridPosition.Print().c_str());
	// }
	App::Print(100,100,App::ScreenToWorld(m_cameraManager.GetMainCamera(), App::GetMousePosVec2()).Print().c_str());
}

void TestGame::InternalShutdown()
{
	delete testSprite;
	delete scheduler;
	
}
