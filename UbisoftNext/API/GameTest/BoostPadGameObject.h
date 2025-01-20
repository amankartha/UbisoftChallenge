#pragma once
#include "GameObject.h"
class BoostPadGameObject :
    public GameObject
{
public:
	BoostPadGameObject(Game* instance,int id);
	void Init() override;
	void Update(float DeltaTime) override;
	void Render() override;
};

