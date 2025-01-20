#pragma once
#include "GameObject.h"

class CGameManager;

class PlayerGameObject : public GameObject
{
public:
	friend class MiniGolfGameManagerGameObject;

	PlayerGameObject(Game* instance, int id,int own_index);
	void Init() override;
	void Update(float DeltaTime) override;

	int GetGolfBallID();
private:
	int m_golf_ball_id;
	int m_ownIndex;
};