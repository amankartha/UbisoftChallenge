#pragma once
#include <Component.h>
#include <vector>
#include <unordered_map>
#include <typeindex>
#include <memory>
#include <string>

class Component;

class GameObject
{
	

private:
	static int ID;
	//Unique Identifier for each Gameobject
	const int id = ID;
	std::unordered_map<std::type_index, std::shared_ptr<Component>> _components;

public:
	std::string name;
	GameObject(const std::string& name  = ""): name(name) 
	{
		ID++;
	}
	virtual void Init();
	virtual void Update();
	virtual void Render();

	//typename... Args is a parameter pack which means it can hold 0 or more types
	// 
	template <typename T, typename... Args>
	void AddComponent(Args&&... args);

	
	int getID() { return id; }


};

