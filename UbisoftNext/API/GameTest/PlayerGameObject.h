#pragma once
#include "GameObject.h"

class PlayerGameObject : public GameObject
{
public:
	friend class GameManager;

	PlayerGameObject(Game* instance, int id);
	void Init() override;
	void Update(float DeltaTime) override;

	int GetGolfBallID();
private:
	int m_golf_ball_id;
};
