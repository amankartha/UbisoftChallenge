#pragma once
#include "GameObject.h"
#include "FSM.h"
#include "State.h"

class PlayerGameObject;



class GameManager : public GameObject
{
public:
	GameManager(Game* instance,int id,int playerCount);
	void Init() override;
	void Update(float DeltaTime) override;
private:
	std::unique_ptr<AI::FSM> m_game_state_machine_;
};
