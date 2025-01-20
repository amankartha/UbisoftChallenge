#pragma once
#include <chrono>

#include "State.h"


enum class PlayerState;
class Crigidbody;
class CGameManager;

class PlayerTurnState : public AI::FSMState
{
public:
	friend CGameManager;
	PlayerTurnState(CGameManager* manager) : m_manager_(manager){}

	void OnEnter() override;
	void OnExit() override;
	void OnUpdate() override;

private:
	Crigidbody* m_current_player_rb;
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

class BallMovingState : public AI::FSMState
{
public:
	friend CGameManager;
	BallMovingState(CGameManager* manager) : m_manager_(manager) {}

	void OnEnter() override;
	void OnExit() override;
	void OnUpdate() override;

private:
	CGameManager* m_manager_;
	Crigidbody* m_crigidbody_;
	PlayerState* m_player_state_;
	std::chrono::time_point<std::chrono::high_resolution_clock> timer;
};
