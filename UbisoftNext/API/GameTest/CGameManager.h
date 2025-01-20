#pragma once
#include "CMiniGolfPlayer.h"
#include "Component.h"
#include "FSM.h"
#include "MiniGolfGameStates.h"

class CMiniGolfPlayer;
class PlayerOneTurnState;

class CGameManager :
    public Component
{
public:
	//Friend classes to states
	friend PlayerOneTurnState;
	//
	CGameManager(GameObject* attachedObject,int playerCount);

	 void Init() override;
	 void Update(float DeltaTime) override;
	 void Render() override;
	 void AddATBToPlayer(int playernumber,int number);
	 bool RemoveATBFromPlayer(int playernumber, int number);
	 int  GetCurrentPlayerIndex();
	 Ctransform* GetCurrentPlayerGolfBallTransform();
	 void StartGame();
private:
	CMiniGolfPlayer* GetMiniGolfPlayer(int index);
	
	void SetMiniGolfPlayerState(int index, PlayerState states);
	void NextPlayerTurn();

public:
	int m_current_player;
private:
	PlayerOneTurnState m_player_one_turn_state_;
	EmptyState m_empty_state_;
private:
	AI::FSM m_game_fsm_;

	std::vector<int> m_player_ATBs_;
	std::vector<int> m_playerGameObjectIds;
	//States

};

