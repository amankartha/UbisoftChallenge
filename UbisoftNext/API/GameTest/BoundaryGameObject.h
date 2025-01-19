#pragma once
#include "GameObject.h"
class BoundaryGameObject :
    public GameObject
{
public:

	BoundaryGameObject(Game* instance, int id);
	void Init() override;
	void Update(float DeltaTime) override;
};

