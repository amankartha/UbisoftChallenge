#include "stdafx.h"
#include "GolfBallGameObject.h"

#include "CGolfBall.h"
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
	AddComponent<Crigidbody>(GameInstance->GetPhysicsSimulation(), 30.0f, 0.3f,0.8f,false);
	AddComponent<CGolfBall>();
	GetComponent<Ctransform>()->SetScale(0.25f);
	GetComponent<Ctransform>()->SetPosition(Vector2(FRAND_RANGE(-50, 50), FRAND_RANGE(-50, 50)));
}

void GolfBallGameObject::Update(float DeltaTime)
{
	GameObject::Update(DeltaTime);

}
