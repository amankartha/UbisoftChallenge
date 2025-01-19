#pragma once
#include "GameObject.h"

class GolfBallGameObject : public GameObject
{
public:
	GolfBallGameObject(Game* instance, int id, GameObject* owner);
	void Init() override;
	void Update(float DeltaTime) override;

private:
	int m_owner_id;
	int m_rigid_body_id;
};
