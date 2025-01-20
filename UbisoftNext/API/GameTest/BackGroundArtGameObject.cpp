#include "stdafx.h"
#include "BackGroundArtGameObject.h"

#include "CRenderer.h"
#include "Game.h"

BackGroundArtGameObject::BackGroundArtGameObject(Game* instance, int id) : GameObject(instance, id)
{
}

void BackGroundArtGameObject::Init()
{
	GameObject::Init();

	AddComponent<CRenderer>(GameInstance->GetRenderer(),true,RenderLayer::Background)->SetSprite(".\\MiniGolfAssets\\grass03.png");
	//GetComponent<CRenderer>()->SetTiled(IntVector2(1,1));
}

void BackGroundArtGameObject::Update(float DeltaTime)
{
	GameObject::Update(DeltaTime);
}
