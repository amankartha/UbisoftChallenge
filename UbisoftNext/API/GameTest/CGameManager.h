#pragma once
#include "Component.h"
#include "FSM.h"
#include "MiniGolfGameStates.h"

class PlayerOneTurnState;

class CGameManager :
    public Component
{
public:
	CGameManager(GameObject* attachedObject);

	 void Init() override;
	 void Update(float DeltaTime) override;
	 void AddATBToPlayer(int playernumber,int number);
	 void RemoveATBFromPlayer(int playernumber, int number);
private:
	AI::FSM m_game_fsm_;

	std::vector<int> m_player_ATBs_;
	//States
private:
	PlayerOneTurnState m_player_one_turn_state_;
};

