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

void GameManager::Update()
{
	GameObject::Update();
}
