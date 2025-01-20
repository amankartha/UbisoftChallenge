#include "stdafx.h"
#include "GolfBallGameObject.h"

#include "CGolfBall.h"
#include "CRenderer.h"
#include "Crigidbody.h"
#include "Game.h"

GolfBallGameObject::GolfBallGameObject(Game* instance, int id, int player_index) : GameObject(instance,id) , m_player_index(player_index)
{
}

void GolfBallGameObject::Init()
{
	GameObject::Init();
	AddComponent<CRenderer>(GameInstance->GetRenderer(), true)->SetSprite(*App::CreateSprite(".\\MiniGolfAssets\\ballGrey_06.png", 1, 1));
	AddComponent<Crigidbody>(GameInstance->GetPhysicsSimulation(), 25.0f, 0.3f,0.8f,false);
	AddComponent<CGolfBall>(m_player_index);
	GetComponent<Ctransform>()->SetScale(0.25f);
	GetComponent<Ctransform>()->SetPosition(Vector2(FRAND_RANGE(-100, 100), FRAND_RANGE(-100, 100)));
}

void GolfBallGameObject::Update(float DeltaTime)
{
	GameObject::Update(DeltaTime);

}
