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
	std::unordered_map<std::type_index, std::shared_ptr<Component>> _components;
	std::shared_ptr<Ctransform> m_transform;
	std::weak_ptr<GameObject> m_selfPointer;

public:
	std::string m_name;
public:
	GameObject()
	{
		
		m_transform = AddComponent<Ctransform>();
	}
	~GameObject()
	{
		
	}
	
	//void SetSelfPointer(std::shared_ptr<GameObject> pointer)
	//{
	//	m_selfPointer = pointer;
	//}

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

		
		component->SetGameObject(*this);

		
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

