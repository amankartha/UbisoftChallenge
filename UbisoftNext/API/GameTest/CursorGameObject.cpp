#include "stdafx.h"
#include "CursorGameObject.h"

#include "Ccursor.h"
#include "CRenderer.h"
#include "Game.h"

CursorGameObject::CursorGameObject(Game* instance) : GameObject(instance)
{
	
}

void CursorGameObject::Init()
{
	GameObject::Init();
	AddComponent<Ccursor>();
	AddComponent<CRenderer>(GameInstance->GetRenderer(), true, RenderLayer::UI)->SetSprite(*App::CreateSprite(".\\TestData\\cursor_pointerFlat.png", 1, 1));
}

void CursorGameObject::Update()
{
	GameObject::Update();
}

CursorGameObject::~CursorGameObject()
{
}
