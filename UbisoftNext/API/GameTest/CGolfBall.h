#pragma once
#include "Component.h"
class CGolfBall :
    public Component
{
public:
	 CGolfBall(GameObject* attachedObject)
		: Component(attachedObject)
	{
	}

	void Init() override;
	void Update(float DeltaTime) override;
};

