#pragma once
#include "GameObject.h"
class BoundaryGameObject :
    public GameObject
{
public:
	BoundaryGameObject(Game* instance, int id,Vector2 position,float width,float height);
	BoundaryGameObject(Game* instance, int id);
	void Init() override;
	void Update(float DeltaTime) override;

private:
	Vector2 m_position;
	float m_width;
	float m_height;
};

