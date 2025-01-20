#pragma once
#include <vector>

#include "Component.h"
struct IntVector2;

class CSmallBall :
    public Component
{
	CSmallBall(GameObject* attachedObject, std::vector<IntVector2> ids);

	~CSmallBall();
	void Init() override;
	void Update(float DeltaTime) override;
	void Render() override;
private:
	std::vector<size_t> m_rigibody_ids;
	std::vector<IntVector2> m_ids_to_clear;
};

