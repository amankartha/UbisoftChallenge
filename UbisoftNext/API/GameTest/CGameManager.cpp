#include "stdafx.h"
#include "CGameManager.h"

CGameManager::CGameManager(GameObject* attachedObject) :Component(attachedObject),
m_player_one_turn_state_(this),
m_game_fsm_(&m_player_one_turn_state_)
{
	
}

void CGameManager::Init()
{
	Component::Init();
}

void CGameManager::Update(float DeltaTime)
{
	Component::Update(DeltaTime);
}

void CGameManager::AddATBToPlayer(int playerNumber, int number)
{
	m_player_ATBs_[playerNumber] = std::clamp(m_player_ATBs_[playerNumber] + number, 0, 10);
}

void CGameManager::RemoveATBFromPlayer(int playerNumber, int number)
{
	m_player_ATBs_[playerNumber] = std::clamp(m_player_ATBs_[playerNumber] - number, 0, 10);
}
