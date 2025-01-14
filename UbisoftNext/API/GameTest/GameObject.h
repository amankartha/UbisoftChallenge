#pragma once
#include "Component.h"
#include "Ctransform.h"
#include <unordered_map>
#include <typeindex>
#include <memory>
#include <string>
#include <iostream>


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
			throw std::logic_error("Component of this type already exists in GameObject");
		}

		m_components[type] = std::make_unique<T>(std::forward<Args>(args)...);

		m_components[type]->SetGameObject(this);

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
	virtual void Update();

	GameObject(Game* gameInstance) : m_components()
	{
		m_isEnabled = false;
		m_parent = nullptr;
		GameInstace = gameInstance;
	};

	~GameObject() = default;

private:
	std::unordered_map<std::type_index, std::unique_ptr<Component>> m_components;
	Game* GameInstace;
public:
	bool m_isEnabled;
	std::string m_name;
	GameObject* m_parent;
	std::vector<GameObject*> m_children;
};
