#include "stdafx.h"
#include "MiniGolfGameStates.h"

#include "CCameraController.h"
#include "CGameManager.h"
#include "CMiniGolfPlayer.h"
#include "Game.h"
#include "GameObjectManager.h"


void PlayerOneTurnState::OnEnter()
{
  m_manager_->SetMiniGolfPlayerState(m_manager_->m_current_player,PlayerState::playing);
  m_manager_->GetAttachedGameObject()->GameInstance->GetGameObjectManager()
	  ->FindUsingTable("MiniGolfCamera")
	  ->GetComponent<CCameraController>()->SetTransformToFollow(m_manager_->GetCurrentPlayerGolfBallTransform());
}

void PlayerOneTurnState::OnExit()
{
}

void PlayerOneTurnState::OnUpdate()
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
