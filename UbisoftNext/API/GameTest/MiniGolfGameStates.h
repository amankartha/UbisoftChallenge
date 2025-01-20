#pragma once
#include "State.h"


class CGameManager;

class PlayerOneTurnState : public AI::FSMState
{
public:
	friend CGameManager;
	PlayerOneTurnState(CGameManager* manager) : m_manager_(manager){}

	void OnEnter() override;
	void OnExit() override;
	void OnUpdate() override;

private:
	CGameManager* m_manager_;
};


class EmptyState : public AI::FSMState
{
public:
	friend CGameManager;
	EmptyState(CGameManager* manager) : m_manager_(manager) {}

	void OnEnter() override;
	void OnExit() override;
	void OnUpdate() override;

private:
	CGameManager* m_manager_;
};
