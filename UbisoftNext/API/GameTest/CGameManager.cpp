#include "stdafx.h"
#include "CGameManager.h"

#include "Game.h"
#include "GameObjectManager.h"
#include "PlayerGameObject.h"
#include "App/app.h"

CGameManager::CGameManager(GameObject* attachedObject,int PlayerCount) :Component(attachedObject),
                                                                        m_player_one_turn_state_(this),
                                                                        m_game_fsm_(&m_player_one_turn_state_)
{
	for (int i = 0;i<PlayerCount;++i)
	{
		m_player_ATBs_.push_back(2);
	}
	m_current_player = 0;
}

void CGameManager::Init()
{
	Component::Init();

	for (int i = 0; i < m_player_ATBs_.size(); ++i)
	{
		m_playerGameObjectIds.push_back(GetAttachedGameObject()->GameInstance->GetGameObjectManager()->Create<PlayerGameObject>("player"));
	}
}

void CGameManager::Update(float DeltaTime)
{
	Component::Update(DeltaTime);
}

void CGameManager::Render()
{
	Component::Render();
	App::Print(20, APP_VIRTUAL_HEIGHT - 20, std::to_string(m_player_ATBs_[0]).c_str());
	App::Print(APP_VIRTUAL_WIDTH - 20, APP_VIRTUAL_HEIGHT - 20, std::to_string(m_player_ATBs_[1]).c_str());
}

void CGameManager::AddATBToPlayer(int playerNumber, int number)
{
	m_player_ATBs_[playerNumber] = std::clamp(m_player_ATBs_[playerNumber] + number, 0, 10);
}

bool CGameManager::RemoveATBFromPlayer(int playerNumber, int number)
{
	if (m_player_ATBs_[playerNumber]- number < 0)
	{
		return false;
	}
	else
	{
		m_player_ATBs_[playerNumber] = std::clamp(m_player_ATBs_[playerNumber] - number, 0, 10);
		return true;
	}
}

int CGameManager::GetCurrentPlayerIndex()
{
	return m_current_player;
}

void CGameManager::NextPlayerTurn()
{
	m_current_player = (m_current_player + 1) % m_player_ATBs_.size();
}
