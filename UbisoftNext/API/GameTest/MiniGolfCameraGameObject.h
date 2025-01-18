#pragma once
#include "GameObject.h"

class MiniGolfCameraGameObject : public GameObject
{
public:
	MiniGolfCameraGameObject(Game* instance);
	void Init() override;
	void Update() override;

};
