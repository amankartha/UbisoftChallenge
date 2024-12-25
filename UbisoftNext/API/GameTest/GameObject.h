#pragma once
#include "Component.h"
#include "Ctransform.h"
#include <vector>
#include <unordered_map>
#include <typeindex>
#include <memory>
#include <string>
#include <iostream>




class GameObject
{
	

private:

	//if the name already exists add the count of the name next to it like how unity does it, default is empty
	static std::string generateUniqueName(const std::string& name)
	{
		std::string modifiedName = name;
		int count = GAMEOBJECTSMAP.count(modifiedName);
		int Counter = 0;
		
		while (count > 0) {
			modifiedName = name + "(" + std::to_string(Counter++) + ")";
			count = GAMEOBJECTSMAP.count(modifiedName);
			
		}

		return modifiedName;
	}

	std::unordered_map<std::type_index, std::shared_ptr<Component>> _components;



	

public:
	std::string m_name;
	
	//This is a map of all the gameobjects in the game currently, if its not in here it doesnt exist or hasnt been loaded in.
	static std::unordered_map<std::string, std::shared_ptr<GameObject>> GAMEOBJECTSMAP; // this shud be an int but keeping it a string because its easier to remember for now

	
	GameObject()
	{
		//GAMEOBJECTSMAP[this->name] = std::shared_ptr<GameObject>(this);
		
	}
	~GameObject()
	{
		
	}

	//ONLY USE THIS TO MAKE GAMEOBJECTS SO THAT THEY ARE STORED IN THE MAP   ---- how to enforce??
	static std::shared_ptr<GameObject> Create(const std::string& name)
	{
		std::string uniqueName = generateUniqueName(name);
		auto newObject = std::make_shared<GameObject>();

	
		GAMEOBJECTSMAP[uniqueName] = newObject;
		GAMEOBJECTSMAP[uniqueName]->m_name = uniqueName;
		GAMEOBJECTSMAP[uniqueName]->AddComponent<Ctransform>();
		
		return newObject;
	}


	virtual void Init();
	virtual void Update();
	virtual void Render();

	//typename... Args is a parameter pack which means it can hold 0 or more types

	


	template <typename T, typename... Args>
	void AddComponent(Args&&... args)
	{
		static_assert(std::is_base_of<Component, T>::value, "T must inherit from Component");  // This splits out an error on compile if I add something thats not a component
		auto type = std::type_index(typeid(T));

		if (_components.find(type) != _components.end()) {  // This makes sure theres only 1 of each type of component added to the GameObject
			throw std::logic_error("Component of this type already exists in GameObject");
		}
		_components[type] = std::make_shared<T>(); //make_shared is to make a shared_ptr and forward forwards the args to the constructor of the template
		_components[type]->SetGameObject(GameObject::GAMEOBJECTSMAP[m_name]);
	}

	template<typename T>
	std::shared_ptr<T> GetComponent()
	{
		auto type = std::type_index(typeid(T));
		if (_components.find(type) != _components.end())
		{
			return std::static_pointer_cast<T>(_components[type]);
		}
		else
		{
			return nullptr;
		}

	}

	template<typename T>
	void RemoveComponent()
	{
		auto type = std::type_index(typeid(T));
		_components.erase(type);
	}



};

