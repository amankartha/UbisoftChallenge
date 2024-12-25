#pragma once
#include <appUtility.h>

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
	std::weak_ptr<GameObject> getAttachedGameObject() { return attachedGameObject; }

	void SetGameObject(std::weak_ptr<GameObject> go)
	{
		attachedGameObject = go;
	}

private:
	std::weak_ptr<GameObject> attachedGameObject;
};

