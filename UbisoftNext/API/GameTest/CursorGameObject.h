#pragma once
#include "GameObject.h"
class CursorGameObject :
    public GameObject
{
public:
	CursorGameObject(Game* instance);

	void Init() override;
	void Update() override;
	~CursorGameObject() override;
	
};

