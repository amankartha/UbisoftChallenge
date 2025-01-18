#include "stdafx.h"
#include "FSM.h"

AI::FSM::FSM(AI::FSMState* initialState)
{
	initialState->OnEnter();
	m_current_state_ = initialState;
}

void AI::FSM::Update()
{
	m_current_state_->OnUpdate();
}

void AI::FSM::Transition(AI::FSMState* nextState)
{
	if (m_current_state_ == nextState)
	{
		return;
	}
	m_current_state_->OnExit();
	nextState->OnEnter();
	m_current_state_ = nextState;
}
