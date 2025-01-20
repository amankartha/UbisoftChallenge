#include "stdafx.h"
#include "Ccursor.h"
#include "GameObject.h"
#include "appUtility.h"
#include "cameraManager.h"
#include "Game.h"
#include "GameObjectManager.h"
#include "Renderer.h"

void Ccursor::Init()
{
	
}

void Ccursor::Update(float DeltaTime)
{
	GetAttachedGameObject()->GetTransformComponent().SetPosition( App::GetMousePosVec2());
}

void Ccursor::Render()
{
	Component::Render();
	Game* game = GetAttachedGameObject()->GameInstance;
	game->GetRenderer()->DrawGridWithCameraAroundTransform(
						&game->GetGameObjectManager()->FindUsingTable("MiniGolfCamera")->GetTransformComponent(),
						*game->GetGridSystem(),
			 &GetAttachedGameObject()->GetTransformComponent());
}
