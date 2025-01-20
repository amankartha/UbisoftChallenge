#include "stdafx.h"
#include "MiniGolfGameStates.h"

#include "CGameManager.h"
#include "CMiniGolfPlayer.h"


void PlayerOneTurnState::OnEnter()
{
  m_manager_->SetMiniGolfPlayerState(m_manager_->m_current_player,PlayerState::playing);
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
