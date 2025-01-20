#pragma once
#include "Component.h"
class CGolfBall;
class CGameManager;

class CMiniGolfPlayer :
    public Component
{
public:
	explicit CMiniGolfPlayer(GameObject* attachedObject,CGameManager* manager,CGolfBall* golfBall);

	void Init() override;
	void Update(float DeltaTime) override;
	void Render() override;
	CGameManager* GetGameManager();
	CGolfBall* GetGolfBall();
private:
	CGameManager* m_game_manager_;
	CGolfBall* m_golf_ball_;
};

