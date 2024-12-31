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

CSimpleSprite* testSprite;
std::shared_ptr<GameObject> player;
std::shared_ptr<GameObject> mouse;
std::shared_ptr<GameObject> camera;
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

	while (ShowCursor(FALSE) >= 0);  //Some code I found online that hides the cursor while its above the window.
	mouse = Create("Mouse");
	player = Create("Player");
	camera = Create("Camera");
	scheduler = new Scheduler();

	m_renderer.SetShake(true);

	
	camera->AddComponent<Ccamera>(m_cameraManager);
	


	mouse->AddComponent<CRenderer>(m_renderer);
	mouse->GetComponent<CRenderer>()->CreateSprite(".\\TestData\\cursor_pointerFlat.png", 1, 1);
	mouse->GetComponent<CRenderer>()->SetRenderLayer(RenderLayer::UI);

	player->AddComponent<CRenderer>(m_renderer);
	player->GetComponent<CRenderer>()->CreateSprite(".\\TestData\\Test.bmp", 8, 4);


	//------------------------------------------------------------------------
	// Example Sprite Code....
	testSprite = App::CreateSprite(".\\TestData\\Test.bmp", 8, 4);
	testSprite->SetPosition(400.0f, 400.0f);
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
	if (App::IsKeyPressed(VK_UP))
	{
		auto g = Create("Generated");
		g->AddComponent<CRenderer>(m_renderer);
		g->GetComponent<CRenderer>()->CreateSprite(".\\TestData\\Test.bmp", 8, 4);

		g->GetTransform()->SetPosition(Vector2(FRAND_RANGE(0, APP_VIRTUAL_WIDTH), FRAND_RANGE(0, APP_VIRTUAL_WIDTH)));
		scheduler->AddTask([this]() { m_renderer.SetShakeOff(); }, 1500);
	}
	if (App::IsKeyPressed(VK_DOWN))
	{
		if (!m_gameObjectMap.empty())
			m_gameObjectMap.erase(std::prev(m_gameObjectMap.end()));
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

	for (auto& it : m_gameObjectMap) {

		it.second->Update();
	}
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
	App::Print(100, 300, std::to_string(m_gameObjectMap.size()).c_str());
	//----------------------------------------------------------------------
	// Render all Gameobjects
	// ---------------------------------------------------------------------


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
	m_renderer.DrawGridWithCamera(m_cameraManager.GetMainCamera(), m_gridSystem);

}

void TestGame::InteralShutdown()
{
	delete testSprite;
	delete scheduler;
}
