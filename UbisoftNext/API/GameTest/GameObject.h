#pragma once
#include <cassert>

#include "Component.h"
#include "Ctransform.h"
#include <unordered_map>
#include <typeindex>
#include <memory>
#include <string>
#include <iostream>
#include "Windows.h"

using CallBack = std::function<void()>;

class Game;

class GameObject
{
public:

	void SetChild(GameObject* childObject);

	void RemoveChild(GameObject* childObject);

	void RemoveParent();

	void SetParent(GameObject* parenteObject);

	Ctransform& GetTransformComponent();

	template <typename T, typename... Args>
	T* AddComponent(Args&&... args)
	{
		static_assert(std::is_base_of_v<Component, T>, "T must inherit from Component");

		auto type = std::type_index(typeid(T));

		if (m_components.contains(type))
		{
			assert("Component of this type already exists in GameObject");
		}

		m_components[type] = std::make_unique<T>(this,std::forward<Args>(args)...);

		m_components[type]->SetGameObject(this);

		m_components[type]->Init();

		return dynamic_cast<T*>(m_components[type].get());
	}

	template <typename T>
	T* GetComponent()
	{
		auto type = std::type_index(typeid(T));
		auto it = m_components.find(type);
		if (it != m_components.end())
		{
			return dynamic_cast<T*>(it->second.get());
		}
		return nullptr;
	}

	template <typename T>
	void RemoveComponent()
	{
		if (std::is_same_v<T, Ctransform>)
		{
			throw std::logic_error("Ctransform cannot be removed.");
			return;
		}

		auto type = std::type_index(typeid(T));
		m_components.erase(type);
	}

	virtual void Init();
	virtual void Update(float DeltaTime);

	GameObject() 
	{
		m_isEnabled = true;
		m_parent = nullptr;
	}

	GameObject(Game* gameInstance, int id = -1) 
	{
		m_isEnabled = true;
		m_parent = nullptr;
		GameInstance = gameInstance;
		m_id = id;
	};


	GameObject(GameObject&& other) noexcept            //move constructor for unique pointers
		: m_components(std::move(other.m_components)),
		GameInstance(other.GameInstance),
		m_isEnabled(other.m_isEnabled),
		m_name(std::move(other.m_name)),
		m_parent(other.m_parent),
		m_children(std::move(other.m_children))
	{
		other.m_parent = nullptr;
		for (auto& [type, component] : m_components) {
			component->SetGameObject(this);
		}
	}

	GameObject& operator=(GameObject&& other) noexcept  //Copy assignment Constructor 
	{
		if (this != &other)
		{
			m_components = std::move(other.m_components);
			GameInstance = other.GameInstance;
			m_isEnabled = other.m_isEnabled;
			m_name = std::move(other.m_name);
			m_parent = other.m_parent;
			m_children = std::move(other.m_children);

			other.m_parent = nullptr;
		}
		return *this;
	}

	GameObject(const GameObject&) = delete;
	GameObject& operator=(const GameObject&) = delete;

	virtual ~GameObject() = default;

protected:
	std::unordered_map<std::type_index, std::unique_ptr<Component>> m_components;
	
public:
	Game* GameInstance;
	bool m_isEnabled;
	std::string m_name;
	GameObject* m_parent;
	std::vector<GameObject*> m_children;
	int m_id;
};
