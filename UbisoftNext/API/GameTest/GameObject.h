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
	Transform& GetTransform() 
	{
		return this->GetComponent<Ctransform>()->GetTransform();
	}
	Ctransform& GetTransformComponent() 
	{
		return *this->GetComponent<Ctransform>();
	}
	template <typename T, typename... Args>
	T* AddComponent(Args&&... args)
	{
		static_assert(std::is_base_of<Component, T>::value, "T must inherit from Component");

		auto type = std::type_index(typeid(T));

		if (m_components.find(type) != m_components.end()) {
			throw std::logic_error("Component of this type already exists in GameObject");
		}

		auto component = std::make_unique<T>(std::forward<Args>(args)...);

		m_components[type] = std::move(component);
		m_components[type]->SetGameObject(this);

		return  dynamic_cast<T*>(m_components[type].get());
	}
	
	template<typename T>
	T* GetComponent()
	{
		auto type = std::type_index(typeid(T));
		auto it = m_components.find(type);
		if (it != m_components.end()) {
			return dynamic_cast<T*>(it->second.get());
		}
		return nullptr;

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

	GameObject()
	{
		
	}
	~GameObject() = default;
private:
	std::unordered_map<std::type_index, std::unique_ptr<Component>> m_components;
	


public:
	std::string m_name;

};

