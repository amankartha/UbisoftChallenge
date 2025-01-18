#include "stdafx.h"
#include "Ccursor.h"
#include "GameObject.h"
#include "appUtility.h"
#include "cameraManager.h"
#include "Game.h"

void Ccursor::Init()
{
	
}

void Ccursor::Update()
{
	GetAttachedGameObject()->GetTransformComponent().SetPosition( App::GetMousePosVec2());
}
