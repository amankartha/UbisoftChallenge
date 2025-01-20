#pragma once
#include "GameObject.h"

class GolfBallGameObject : public GameObject
{
public:
	GolfBallGameObject(Game* instance, int id, int player_index);
	void Init() override;
	void Update(float DeltaTime) override;

private:
	int m_rigid_body_id;
	int m_player_index;
};
