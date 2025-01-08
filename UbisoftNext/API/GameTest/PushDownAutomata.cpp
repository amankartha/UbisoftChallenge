#include "stdafx.h"
#include "PushDownAutomata.h"
#include "state.h"

AI::State* AI::PushDownAutomata::GetCurrentState() 
{
	if (!m_stateStack.empty())
	{
		return m_stateStack.top();
	}
	return nullptr;
}

void AI::PushDownAutomata::PushState(State& state)
{
	m_stateStack.push(&state);
	state.Enter();
}

void AI::PushDownAutomata::PopState()
{
	if (m_stateStack.empty())
	{
		return;
	}
	GetCurrentState()->Exit();
	m_stateStack.pop();
}

void AI::PushDownAutomata::UpdateState()
{
	if (!m_stateStack.empty())
	{
		GetCurrentState()->Update();
	}
}

void AI::PushDownAutomata::SetContext(Context context)
{
	m_context = context;
}
