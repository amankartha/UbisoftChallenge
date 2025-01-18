#pragma once
#include "GameObject.h"
#include "FSM.h"
#include "State.h"

class PlayerGameObject;

class Player1State : public AI::FSMState
{
public:
	void OnEnter() override;
	void OnExit() override; 
	void OnUpdate() override;
};



class GameManager : public GameObject
{
public:
	GameManager(Game* instance,int id);
	void Init() override;
	void Update() override;
private:
	int m_player1_id;
	int m_player2_id;
	std::unique_ptr<AI::FSM> m_game_state_machine_;
};
