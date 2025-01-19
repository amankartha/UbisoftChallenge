#include "stdafx.h"
#include "GolfBallGameObject.h"

#include "CRenderer.h"
#include "Crigidbody.h"
#include "Game.h"

GolfBallGameObject::GolfBallGameObject(Game* instance, int id, GameObject* owner) : GameObject(instance,id) , m_owner_id(owner->m_id)
{
}

void GolfBallGameObject::Init()
{
	GameObject::Init();
	AddComponent<CRenderer>(GameInstance->GetRenderer(), true)->SetSprite(*App::CreateSprite(".\\MiniGolfAssets\\ballGrey_06.png", 1, 1));
	AddComponent<Crigidbody>(GameInstance->GetPhysicsSimulation(), 15.0f, 1.0f,false);
	GetComponent<Ctransform>()->SetScale(0.25f);
}

void GolfBallGameObject::Update(float DeltaTime)
{
	GameObject::Update(DeltaTime);

}
