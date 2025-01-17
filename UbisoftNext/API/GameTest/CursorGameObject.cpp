#include "stdafx.h"
#include "CursorGameObject.h"

#include "Ccursor.h"
#include "CRenderer.h"
#include "Game.h"

CursorGameObject::CursorGameObject(Game* instance) : GameObject(instance)
{
	AddComponent<Ccursor>();
	AddComponent<CRenderer>(instance->GetRenderer(),true,RenderLayer::UI)->SetSprite(*App::CreateSprite(".\\TestData\\cursor_pointerFlat.png", 1, 1));
}

void CursorGameObject::Init()
{
	GameObject::Init();
}

void CursorGameObject::Update()
{
	GameObject::Update();
}

CursorGameObject::~CursorGameObject()
{
}
