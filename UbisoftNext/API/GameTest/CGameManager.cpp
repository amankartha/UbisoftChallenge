#include "stdafx.h"
#include "CGameManager.h"

#include "CMiniGolfPlayer.h"
#include "Game.h"
#include "GameObjectManager.h"
#include "PlayerGameObject.h"
#include "App/app.h"

CGameManager::CGameManager(GameObject* attachedObject,int PlayerCount) :Component(attachedObject),
                                                                        m_player_one_turn_state_(this),
																		m_empty_state_(this),
                                                                        m_game_fsm_(&m_empty_state_)
{
	for (int i = 0;i<PlayerCount;++i)
	{
		m_player_ATBs_.push_back(2);
		m_playerGameObjectIds.push_back(GetAttachedGameObject()->GameInstance->GetGameObjectManager()->Create<PlayerGameObject>("player", i));
	}
	m_current_player = 0;
}

void CGameManager::Init()
{
	Component::Init();

	//for (int i = 0; i < m_player_ATBs_.size(); ++i)
	//{
	//	m_playerGameObjectIds.push_back(GetAttachedGameObject()->GameInstance->GetGameObjectManager()->Create<PlayerGameObject>("player",i));
	//}

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
	App::Print(APP_VIRTUAL_WIDTH / 2, APP_VIRTUAL_HEIGHT - 20, ("It\'s player" + std::to_string(m_current_player + 1) + "'s turn").c_str());
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

void CGameManager::StartGame()
{
	m_game_fsm_.Transition(&m_player_one_turn_state_);
}

CMiniGolfPlayer* CGameManager::GetMiniGolfPlayer(int index)
{
	return GetAttachedGameObject()->GameInstance->GetGameObjectManager()->Find(m_playerGameObjectIds[index])->GetComponent<CMiniGolfPlayer>();
}

void CGameManager::SetMiniGolfPlayerState(int index, PlayerState states)
{
	GetMiniGolfPlayer(index)->SetState(states);
}

void CGameManager::NextPlayerTurn()
{
	m_current_player = (m_current_player + 1) % m_player_ATBs_.size();
}
