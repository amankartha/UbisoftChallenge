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
	std::shared_ptr<Ctransform> m_transform;

public:
	std::string m_name;
	
	//This is a map of all the gameobjects in the game currently, if its not in here it doesnt exist or hasnt been loaded in.
	static std::unordered_map<std::string, std::shared_ptr<GameObject>> GAMEOBJECTSMAP; // this shud be a GUID but keeping it a string because its easier to remember for now

	
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
		auto createdGO = std::make_shared<GameObject>();
		createdGO->m_name = uniqueName;
		createdGO->m_transform = createdGO->AddComponent<Ctransform>();
		GAMEOBJECTSMAP[uniqueName] = createdGO;
		
		return createdGO;
	}
	//ONLY USE THIS TO DESTROY GAMEOBJECTS
	static void Destroy(const std::string& name)
	{
		GAMEOBJECTSMAP.erase(name);
	}
	static void Destroy(std::shared_ptr<GameObject> go)
	{
		GAMEOBJECTSMAP.erase(go->m_name);
	}

	//returns a weak pointer to this gameobjects transform;
	std::shared_ptr<Ctransform> GetTransform()
	{
		return m_transform;
	}
	//Adds component to the gameobject and returns it
	template <typename T, typename... Args>
	std::shared_ptr<T> AddComponent(Args&&... args)
	{
		static_assert(std::is_base_of<Component, T>::value, "T must inherit from Component");

		auto type = std::type_index(typeid(T));

		if (_components.find(type) != _components.end()) {
			throw std::logic_error("Component of this type already exists in GameObject");
		}

		
		auto component = std::make_shared<T>(std::forward<Args>(args)...);

		
		component->SetGameObject(GameObject::GAMEOBJECTSMAP[m_name]);

		
		_components[type] = component;

		return component;
	}
	//Returns a shared pointer to the component
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
	//Remove component type from this gameobject, Cannot remove Ctransform
	template<typename T>
	void RemoveComponent()
	{
		if (std::is_same<T, Ctransform>::value) {
			throw std::logic_error("Ctransform cannot be removed.");
			return;
		}

		auto type = std::type_index(typeid(T));
		_components.erase(type);
	}




	virtual void Init();
	virtual void Update();
	virtual void Render();


};

