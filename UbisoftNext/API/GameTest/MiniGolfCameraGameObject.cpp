#include "stdafx.h"
#include "MiniGolfCameraGameObject.h"

#include "Ccamera.h"
#include "CCameraController.h"
#include "Game.h"

MiniGolfCameraGameObject::MiniGolfCameraGameObject(Game* instance,int id) : GameObject(instance,id)
{

}

void MiniGolfCameraGameObject::Init()
{
	GameObject::Init();
	AddComponent<Ccamera>(GameInstance->GetCameraManager(), 1);
	AddComponent<CCameraController>();
	GameInstance->GetCameraManager()->SetMainCamera(1);
	GetComponent<Ccamera>()->SetTransform(&GetTransformComponent());  //TODO: this is bad
}

void MiniGolfCameraGameObject::Update(float DeltaTime)
{
	GameObject::Update(DeltaTime);
}

