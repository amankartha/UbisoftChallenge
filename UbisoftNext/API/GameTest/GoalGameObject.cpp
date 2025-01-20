#include "stdafx.h"
#include "GoalGameObject.h"

#include "CGoal.h"
#include "CRenderer.h"
#include "Crigidbody.h"
#include "Game.h"



GoalGameObject::GoalGameObject(Game* instance, int id, std::vector<IntVector2> idsToClearOnDestroy) : GameObject(instance,id), m_idsToClear(idsToClearOnDestroy)
{
}

void GoalGameObject::Init()
{
	GameObject::Init();
	AddComponent<CRenderer>(GameInstance->GetRenderer(), true)->SetSprite(*App::CreateSprite(".\\MiniGolfAssets\\hole_large.png", 1, 1));
	AddComponent<Crigidbody>(GameInstance->GetPhysicsSimulation(), 150.0f, 150.0f, 0.3f, 0.8f, false, true);
	
	GetComponent<Ctransform>()->SetScale(1.0f);
	AddComponent<CGoal>(m_idsToClear);
	
}

void GoalGameObject::Update(float DeltaTime)
{
	GameObject::Update(DeltaTime);
}

void GoalGameObject::Render()
{
	GameObject::Render();
}
