#pragma once
#include "GameObject.h"
class BoostPadGameObject :
    public GameObject
{
public:
	BoostPadGameObject(Game* instance,int id,std::vector<IntVector2> idsToClearOnDestroy);
	void Init() override;
	void Update(float DeltaTime) override;
	void Render() override;

private:
	std::vector<IntVector2> m_idsToClear;
};

