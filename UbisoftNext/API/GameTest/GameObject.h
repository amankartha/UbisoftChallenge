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
public:
	std::shared_ptr<Ctransform> GetTransform()
	{
		return m_transform;
	}
	template <typename T, typename... Args>
	std::shared_ptr<T> AddComponent(Args&&... args)
	{
		static_assert(std::is_base_of<Component, T>::value, "T must inherit from Component");

		auto type = std::type_index(typeid(T));

		if (m_components.find(type) != m_components.end()) {
			throw std::logic_error("Component of this type already exists in GameObject");
		}

		
		auto component = std::make_shared<T>(std::forward<Args>(args)...);

		
		component->SetGameObject(*this);

		
		m_components[type] = component;

		return component;
	}
	
	template<typename T>
	std::shared_ptr<T> GetComponent()
	{
		auto type = std::type_index(typeid(T));
		if (m_components.find(type) != m_components.end())
		{
			return std::static_pointer_cast<T>(m_components[type]);
		}
		else
		{
			return nullptr;
		}

	}
	
	template<typename T>
	void RemoveComponent()
	{
		if (std::is_same<T, Ctransform>::value) {
			throw std::logic_error("Ctransform cannot be removed.");
			return;
		}

		auto type = std::type_index(typeid(T));
		m_components.erase(type);
	}
	virtual void Init();
	virtual void Update();
private:
	GameObject()
	{
		m_transform = AddComponent<Ctransform>();
	}
	~GameObject() = default;
private:
	std::unordered_map<std::type_index, std::shared_ptr<Component>> m_components;
	std::shared_ptr<Ctransform> m_transform;


public:
	std::string m_name;

};

