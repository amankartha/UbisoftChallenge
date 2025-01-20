#include "stdafx.h"
#include "MiniGolfGameManagerGameObject.h"

#include "CGameManager.h"
#include "Game.h"
#include "GameObjectManager.h"
#include "PlayerGameObject.h"

MiniGolfGameManagerGameObject::MiniGolfGameManagerGameObject(Game* instance,int id,int playerCount): GameObject(instance,id)
{
}



void MiniGolfGameManagerGameObject::Init() 
{
	GameObject::Init();
	AddComponent<CGameManager>(2);

	//m_player1_id = GameInstance->GetGameObjectManager()->Create<PlayerGameObject>("player1");
	//m_player2_id = instance->GetGameObjectManager()->Create<PlayerGameObject>("player2");
}

void MiniGolfGameManagerGameObject::Update(float DeltaTime) 
{
	GameObject::Update(DeltaTime);
}

