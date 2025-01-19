#include "stdafx.h"
#include "BoundaryGameObject.h"

#include "Crigidbody.h"
#include "Game.h"

BoundaryGameObject::BoundaryGameObject(Game* instance, int id) : GameObject(instance, id)
{
}

void BoundaryGameObject::Init()
{
	GameObject::Init();
	AddComponent<Crigidbody>(GameInstance->GetPhysicsSimulation(), 1000.0f,30.0f ,0.3f, 0.8f, true);
}

void BoundaryGameObject::Update(float DeltaTime)
{
	GameObject::Update(DeltaTime);
}
