#include "stdafx.h"
#include "GameManager.h"

#include "CGameManager.h"
#include "Game.h"
#include "GameObjectManager.h"
#include "PlayerGameObject.h"

GameManager::GameManager(Game* instance,int id,int playerCount): GameObject(instance,id)
{
}



void GameManager::Init() 
{
	GameObject::Init();
	AddComponent<CGameManager>(2);

	//m_player1_id = GameInstance->GetGameObjectManager()->Create<PlayerGameObject>("player1");
	//m_player2_id = instance->GetGameObjectManager()->Create<PlayerGameObject>("player2");
}

void GameManager::Update(float DeltaTime) 
{
	GameObject::Update(DeltaTime);
}

