#pragma once
#include <memory>

class GameObject;

class Component
{
	

public:
	bool enabled = true;
	GameObject* attachedGameObject;
public:
	Component()
	{
		attachedGameObject = 0;
	};
	virtual ~Component() = default;
	virtual void Init() {};
	virtual void Update() {};

	
	 GameObject* getAttachedGameObject() { return attachedGameObject; }

	void SetGameObject(GameObject* go)  {   attachedGameObject = go;  }

};

