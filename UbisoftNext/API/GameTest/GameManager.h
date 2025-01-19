#pragma once
#include "GameObject.h"
#include "FSM.h"
#include "State.h"

class PlayerGameObject;



class GameManager : public GameObject
{
public:
	GameManager(Game* instance,int id);
	void Init() override;
	void Update(float DeltaTime) override;
	int GetPlayerID(bool player);
private:
	int m_player1_id;
	int m_player2_id;
	std::unique_ptr<AI::FSM> m_game_state_machine_;
};
