#include "stdafx.h"
#include "MiniGolfCameraGameObject.h"

#include "Ccamera.h"
#include "CCameraController.h"
#include "Game.h"

MiniGolfCameraGameObject::MiniGolfCameraGameObject(Game* instance,int id) : GameObject(instance,id)
{
	AddComponent<Ccamera>(GameInstance->GetCameraManager(), 1);
	AddComponent<CCameraController>();
	GameInstance->GetCameraManager()->SetMainCamera(1);
}

void MiniGolfCameraGameObject::Init()
{
	GameObject::Init();
	GetComponent<Ccamera>()->SetTransform(&GetTransformComponent());  //TODO: this is bad
}

void MiniGolfCameraGameObject::Update(float DeltaTime)
{
	GameObject::Update(DeltaTime);
}

