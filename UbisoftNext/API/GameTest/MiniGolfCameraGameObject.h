#pragma once
#include "GameObject.h"

class MiniGolfCameraGameObject : public GameObject
{
public:
	MiniGolfCameraGameObject(Game* instance,int id);
	void Init() override;
	void Update() override;

};
