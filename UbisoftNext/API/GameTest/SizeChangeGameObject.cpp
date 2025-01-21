#include "stdafx.h"
#include "SizeChangeGameObject.h"

#include "CChangeSize.h"
#include "CRenderer.h"
#include "Crigidbody.h"
#include "Game.h"

SizeChangeGameObject::SizeChangeGameObject(Game* instance, int id, std::vector<IntVector2> idsToClearOnDestroy) : GameObject(instance, id),
                                                                                                                  m_idsToClear(idsToClearOnDestroy)
{

}

void SizeChangeGameObject::Init()
{
	GameObject::Init();
	AddComponent<CRenderer>(GameInstance->GetRenderer(), true)->SetSprite(*App::CreateSprite(".\\MiniGolfAssets\\tile_plus.png", 1, 1));
	AddComponent<Crigidbody>(GameInstance->GetPhysicsSimulation(), 150.0f, 150.0f, 0.3f, 0.8f, false, true);
	//AddComponent<CGolfBall>(m_player_index, m_player_id);
	GetComponent<Ctransform>()->SetScale(1.0f);
	//GetComponent<Ctransform>()->SetPosition(Vector2(0,300));
	AddComponent<CChangeSize>(m_idsToClear);
}

void SizeChangeGameObject::Update(float DeltaTime)
{
	GameObject::Update(DeltaTime);
}

void SizeChangeGameObject::Render()
{
	GameObject::Render();
}
