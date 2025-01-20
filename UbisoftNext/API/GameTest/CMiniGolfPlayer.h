#pragma once
#include "Component.h"
class CGolfBall;
class CGameManager;

enum class PlayerState
{
	idle,
	playing
};

class CMiniGolfPlayer :
    public Component
{
public:
	friend class CGameManager; //intentional Coupling
	explicit CMiniGolfPlayer(GameObject* attachedObject,int golf_ball_id,CGameManager* gm = nullptr);

	void Init() override;
	void Update(float DeltaTime) override;
	void Render() override;

	PlayerState m_state_;
	CGameManager* GetGameManager();
	CGolfBall* GetGolfBall();
private:
	void SetState(PlayerState state);
	CGameManager* m_game_manager_;
	CGolfBall* m_golf_ball_;
	
	int m_golf_ball_id;
};

