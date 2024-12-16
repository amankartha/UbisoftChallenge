#pragma once

class GameObject;

class Component
{
public:
	Component(GameObject* go) { attachedGameObject = go; }
	virtual ~Component(){}
	
	//get the gameobject that this component is attached to
	GameObject* getAttachedGameObject() { return attachedGameObject; }

private:
	GameObject* attachedGameObject = nullptr;
};

