#pragma once
#include "State.h"


class CGameManager;

class PlayerOneTurnState : public AI::FSMState
{
public:
	PlayerOneTurnState(CGameManager* manager) : m_manager_(manager){}

	void OnEnter() override;
	void OnExit() override;
	void OnUpdate() override;

private:
	CGameManager* m_manager_;
};

