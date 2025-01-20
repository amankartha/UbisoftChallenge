#include "stdafx.h"
#include "ExtraBallGameObject.h"

#include "CRenderer.h"
#include "Crigidbody.h"
#include "Game.h"
#include "GameObjectManager.h"
#include "Scheduler.h"



ExtraBallGameObject::ExtraBallGameObject(Game* instance, int id, std::vector<IntVector2> idsToClearOnDestroy): GameObject(instance, id),
                                                                                                               m_idsToClear(idsToClearOnDestroy)
{

}

void ExtraBallGameObject::Init()
{
	GameObject::Init();
	AddComponent<CRenderer>(GameInstance->GetRenderer(), true)->SetSprite(*App::CreateSprite(".\\MiniGolfAssets\\ball_blue_small.png", 1, 1));
	AddComponent<Crigidbody>(GameInstance->GetPhysicsSimulation(), 25.0f, 0.2f, 1.0f, false, false);
	
	//GetComponent<Ctransform>()->SetScale(3.0f);
	auto id = m_id;
	auto manager = GameInstance->GetGameObjectManager();
	GameInstance->GetScheduler()->AddTask([manager,id]() {manager->Destroy(id); },20000);
	
}

void ExtraBallGameObject::Update(float DeltaTime)
{
	GameObject::Update(DeltaTime);
}

void ExtraBallGameObject::Render()
{
	GameObject::Render();
}

