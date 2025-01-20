#pragma once
#include "GameObject.h"
class BackGroundArtGameObject :
    public GameObject
{
public:

	BackGroundArtGameObject(Game* instance, int id);
	void Init() override;
	void Update(float DeltaTime) override;
};

