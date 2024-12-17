#pragma once

class GameObject;

class Component
{
public:
	bool enabled = true;

public:
	Component(GameObject* go) { attachedGameObject = go; }
	virtual ~Component(){}
	
	virtual void Init() {};
	virtual void Update() {};
	virtual void Render() {};

	//get the gameobject that this component is attached to
	GameObject* getAttachedGameObject() { return attachedGameObject; }

private:
	GameObject* attachedGameObject = nullptr;
};

