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
	static std::unordered_map<std::string, std::shared_ptr<GameObject>> GAMEOBJECTSMAP;
	
	std::unordered_map<std::type_index, std::shared_ptr<Component>> _components;



	std::string generateUniqueName(const std::string& name)
	{
		std::string modifiedName = name;
		if (GAMEOBJECTSMAP.find(name) != GAMEOBJECTSMAP.end())
		{
			modifiedName = name + "(" + std::to_string(GAMEOBJECTSMAP.count(name)) + ")";
		}
		return modifiedName;
	}

public:
	std::string name;

	//Constructor attempts to make a game object with the name given, if the name already exists add the count of the name next to it like how unity does it, default is empty
	GameObject(const std::string& name  = ""): name(generateUniqueName(name)) 
	{
		GAMEOBJECTSMAP[this->name] = std::make_shared<GameObject>(*this);
	}
	virtual void Init();
	virtual void Update();
	virtual void Render();

	//typename... Args is a parameter pack which means it can hold 0 or more types

	template <typename T, typename... Args>
	void AddComponent(Args&&... args);

	



};

