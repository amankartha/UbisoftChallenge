#pragma once
#include <memory>

class GameObject;

class Component
{
public:
	bool enabled = true;

public:
	Component() = default;
	virtual ~Component() = default;
	
	virtual void Init() {};
	virtual void Update() {};
	virtual void Render() {};

	//get the gameobject that this component is attached to
	 GameObject* getAttachedGameObject() { return attachedGameObject; }

	void SetGameObject(GameObject& go)
	{
		attachedGameObject = &go;
	}

private:
	GameObject* attachedGameObject;
};

