#include "stdafx.h"
#include "GameManager.h"

#include "Game.h"
#include "GameObjectManager.h"
#include "PlayerGameObject.h"

GameManager::GameManager(Game* instance,int id): GameObject(instance,id)
{
	m_player1_id = instance->GetGameObjectManager()->Create<PlayerGameObject>("player1") ;
	m_player2_id = instance->GetGameObjectManager()->Create<PlayerGameObject>("player2");
}



void GameManager::Init()
{
	GameObject::Init();
}

void GameManager::Update(float DeltaTime)
{
	GameObject::Update(DeltaTime);
}

int GameManager::GetPlayerID(bool player)
{
	if (player)
	{
		return m_player2_id;
	}
	else
	{
		return m_player1_id;
	}
}
