#include "stdafx.h"
#include "MiniGolfGameStates.h"

#include "CCameraController.h"
#include "CGameManager.h"
#include "CGolfBall.h"
#include "CMiniGolfPlayer.h"
#include "Crigidbody.h"
#include "Game.h"
#include "GameObjectManager.h"


void PlayerTurnState::OnEnter()
{
	m_manager_->GetPlayerGolfBall(m_manager_->GetPreviousPlayerIndex())->RemoveGameManagerObserver(m_manager_);
	m_manager_->AddATBToPlayer(m_manager_->m_current_player, 3);
  m_manager_->SetMiniGolfPlayerState(m_manager_->m_current_player,PlayerState::playing);
  m_manager_->GetAttachedGameObject()->GameInstance->GetGameObjectManager()
	  ->FindUsingTable("MiniGolfCamera")
	  ->GetComponent<CCameraController>()->SetTransformToFollow(m_manager_->GetCurrentPlayerGolfBallTransform());
  m_manager_->GetCurrentPlayerGolfBall()->RegisterGameManagerObserver(m_manager_);
}

void PlayerTurnState::OnExit()
{
	
}

void PlayerTurnState::OnUpdate()
{
	
}

void EmptyState::OnEnter()
{
}

void EmptyState::OnExit()
{
}

void EmptyState::OnUpdate()
{
}

void BallMovingState::OnEnter()
{
	m_crigidbody_ = m_manager_->GetCurrentPlayerGolfBall()->GetRigidBody();
	timer = std::chrono::high_resolution_clock::now();
}

void BallMovingState::OnExit()
{
}

void BallMovingState::OnUpdate()
{
	auto current_time = std::chrono::high_resolution_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::duration<double>>(current_time - timer);
	if ( elapsed.count() > 3 &&  m_crigidbody_->GetVelocity().MagnitudeSquared() < 0.1f)
	{
		m_manager_->NextPlayerTurn();
		m_manager_->Transition(&m_manager_->m_player_one_turn_state_);
	}

}
