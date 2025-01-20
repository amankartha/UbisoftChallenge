#pragma once
#include "CMiniGolfPlayer.h"
#include "Component.h"
#include "FSM.h"
#include "MiniGolfGameStates.h"

class CMiniGolfPlayer;
class PlayerTurnState;

class CGameManager :
    public Component , public Events::IObserver
{
public:
	//Friend classes to states
	friend PlayerTurnState;
	friend BallMovingState;
	//
	CGameManager(GameObject* attachedObject,int playerCount);

	 void Init() override;
	 void Update(float DeltaTime) override;
	 void Render() override;
	 void AddATBToPlayer(int playernumber,int number);
	 bool RemoveATBFromPlayer(int playernumber, int number);
	 int  GetCurrentPlayerIndex();
	 Ctransform* GetCurrentPlayerGolfBallTransform();
	 CGolfBall* GetCurrentPlayerGolfBall();
	 CGolfBall* GetPlayerGolfBall(int index);
	 std::vector<size_t> GetAllGolfBallRigidBodies();
	 void StartGame();
	 int GetPreviousPlayerIndex();
	 void AddScoreToCurrentPlayer();
private:
	CMiniGolfPlayer* GetMiniGolfPlayer(int index);
	void SetMiniGolfPlayerState(int index, PlayerState states);
	void NextPlayerTurn();
	void Transition(AI::FSMState* state);


public:
	void OnNotify(Events::EventType event) override;

	int m_current_player;
private:
	PlayerTurnState m_player_one_turn_state_;
	EmptyState m_empty_state_;
	BallMovingState moving_state_;
private:
	AI::FSM m_game_fsm_;

	std::vector<int> m_player_ATBs_;
	std::vector<int> m_playerGameObjectIds;
	std::vector<int> m_playerScores;
	int m_turn_counter_;
	//States

};

inline void CGameManager::OnNotify(Events::EventType event)
{
	if (event == Events::EventType::BallHit)
	{
		Transition(&moving_state_);
		SetMiniGolfPlayerState(m_current_player, PlayerState::idle);
	}
}

