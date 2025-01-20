#include "stdafx.h"
#include "BoostPadGameObject.h"

#include "CBoostPad.h"
#include "CRenderer.h"
#include "Crigidbody.h"
#include "Game.h"

BoostPadGameObject::BoostPadGameObject(Game* instance, int id, std::vector<IntVector2> idsToClearOnDestroy) : GameObject(instance, id),
m_idsToClear(idsToClearOnDestroy)
{
	
}

void BoostPadGameObject::Init()
{
	GameObject::Init();
	AddComponent<CRenderer>(GameInstance->GetRenderer(), true)->SetSprite(*App::CreateSprite(".\\MiniGolfAssets\\Boost_Arrows.png", 1, 1));
	AddComponent<Crigidbody>(GameInstance->GetPhysicsSimulation(), 150.0f,150.0f, 0.3f, 0.8f, false,true);
	//AddComponent<CGolfBall>(m_player_index, m_player_id);
	GetComponent<Ctransform>()->SetScale(3.0f);
	//GetComponent<Ctransform>()->SetPosition(Vector2(0,300));
	AddComponent<CBoostPad>(m_idsToClear);
}

void BoostPadGameObject::Update(float DeltaTime)
{
	GameObject::Update(DeltaTime);
}

void BoostPadGameObject::Render()
{
	GameObject::Render();
}
