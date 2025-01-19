#include "stdafx.h"
#include "CursorGameObject.h"

#include "Ccursor.h"
#include "CPlaceObject.h"
#include "CRenderer.h"
#include "Crigidbody.h"
#include "Game.h"

CursorGameObject::CursorGameObject(Game* instance,int id) : GameObject(instance,id)
{
	AddComponent<Ccursor>();
	AddComponent<CRenderer>(GameInstance->GetRenderer(), true, RenderLayer::UI);  
	AddComponent<CPlaceObject>(GameInstance->GetInputHandler(), GameInstance->GetGridSystem());

}

void CursorGameObject::Init()
{
	GameObject::Init();
	GetComponent<CRenderer>()->SetSprite(*App::CreateSprite(".\\TestData\\cursor_pointerFlat.png", 1, 1));
	//AddComponent<Crigidbody>(GameInstance->GetPhysicsSimulation(), 15.0f,15.0f, 1.0f,0.8f,true);
}

void CursorGameObject::Update(float DeltaTime)
{
	GameObject::Update(DeltaTime);
}

CursorGameObject::~CursorGameObject()
{
}
