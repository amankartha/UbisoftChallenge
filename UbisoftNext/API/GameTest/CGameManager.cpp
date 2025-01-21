#include "stdafx.h"
#include "CGameManager.h"

#include "CGolfBall.h"
#include "CMiniGolfPlayer.h"
#include "Crigidbody.h"
#include "Game.h"
#include "GameObjectManager.h"
#include "PlayerGameObject.h"
#include "App/app.h"

CGameManager::CGameManager(GameObject* attachedObject,int PlayerCount) : Component(attachedObject),
                                                                        m_player_one_turn_state_(this),
																		m_empty_state_(this),
                                                                        m_game_fsm_(&m_empty_state_),
																		moving_state_(this),
																		m_turn_counter_(0)
{
	for (int i = 0;i<PlayerCount;++i)
	{
		m_player_ATBs_.push_back(4);
		m_playerScores.push_back(0);
		m_playerGameObjectIds.push_back(GetAttachedGameObject()->GameInstance->GetGameObjectManager()->Create<PlayerGameObject>("player", i));
	}
	m_current_player = 0;
}

void CGameManager::Init()
{
	Component::Init();
}

void CGameManager::Update(float DeltaTime)
{
	Component::Update(DeltaTime);
	m_game_fsm_.Update();
}

void CGameManager::Render()
{
	Component::Render();
	App::Print(20, APP_VIRTUAL_HEIGHT - 20, std::to_string(m_player_ATBs_[0]).c_str());
	App::Print(APP_VIRTUAL_WIDTH - 100, APP_VIRTUAL_HEIGHT - 20, std::to_string(m_player_ATBs_[1]).c_str());

	App::Print(20, APP_VIRTUAL_HEIGHT - 50, ("Score:  " + std::to_string(m_playerScores[0])).c_str());
	App::Print(APP_VIRTUAL_WIDTH - 100, APP_VIRTUAL_HEIGHT - 50, ("Score:  " + std::to_string(m_playerScores[1])).c_str());

	App::Print( 150, APP_VIRTUAL_HEIGHT - 20, ("Turn Number: " + std::to_string(m_turn_counter_)).c_str());
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

Ctransform* CGameManager::GetCurrentPlayerGolfBallTransform()
{
	return GetMiniGolfPlayer(m_current_player)->GetGolfBall()->GetAttachedGameObject()->GetComponent<Ctransform>();
}

CGolfBall* CGameManager::GetCurrentPlayerGolfBall()
{
	return GetMiniGolfPlayer(m_current_player)->GetGolfBall();
}

CGolfBall* CGameManager::GetPlayerGolfBall(int index)
{
	return GetMiniGolfPlayer(index)->GetGolfBall();
}

std::vector<size_t> CGameManager::GetAllGolfBallRigidBodies()
{
	std::vector<size_t> ids;
	for (int i = 0; i < m_playerGameObjectIds.size(); ++i)
		ids.push_back(GetPlayerGolfBall(i)->GetRigidBody()->GetRigidBodyId());
	return ids;
}


void CGameManager::StartGame()
{
	m_game_fsm_.Transition(&m_player_one_turn_state_);
}

int CGameManager::GetPreviousPlayerIndex()
{
	return (m_current_player - 1) % m_player_ATBs_.size();
}

void CGameManager::AddScoreToCurrentPlayer()
{
	m_playerScores[m_current_player] += 1;
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

void CGameManager::Transition(AI::FSMState* state)
{
	m_game_fsm_.Transition(state);
}
