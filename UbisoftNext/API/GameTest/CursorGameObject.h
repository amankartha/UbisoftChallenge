#pragma once
#include "GameObject.h"
class CursorGameObject :
    public GameObject
{
public:
	CursorGameObject(Game* instance,int id);

	void Init() override;
	void Update(float DeltaTime) override;
	~CursorGameObject() override;
	
};

