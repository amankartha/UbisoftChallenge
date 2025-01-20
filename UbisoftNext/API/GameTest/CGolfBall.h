#pragma once
#include "Component.h"
class CGolfBall :
    public Component
{
public:
	 CGolfBall(GameObject* attachedObject,int OwnerIndex)
		: Component(attachedObject)
	{
	}

	void Init() override;
	void Update(float DeltaTime) override;

private:
	int m_owner_index_;
};

