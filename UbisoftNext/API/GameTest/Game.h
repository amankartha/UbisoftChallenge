#pragma once
#include "PhysicsSimulation.h"
#include <memory>
#include "Renderer.h"
#include "GameObject.h"
#include "Scheduler.h"
class Game
{
protected:
	std::unique_ptr<PHYSICS::PhysicsSimulation> m_physicsSimulation;
	std::unique_ptr<Renderer> m_renderer;
	std::unordered_map<std::string, std::shared_ptr<GameObject>> m_gameObjectMap;
	Scheduler* scheduler;
public:
	Game() 
	{
		m_physicsSimulation = std::make_unique<PHYSICS::PhysicsSimulation>(9.81f);
		m_renderer = std::make_unique<Renderer>();
	}
	~Game() {}

	virtual void InternalInit() = 0;
	virtual	void InternalUpdate(const float deltaTime) = 0;
	virtual void InternalRender() = 0;
	virtual void InteralShutdown() = 0;


	/// <summary>
	/// Create a Gameobject
	/// </summary>
	/// <param name="name">The name of the gameobject which will also be used as a key to find it</param>
	/// <returns></returns>
	std::shared_ptr<GameObject> Create(const std::string& name)
	{
		std::string uniqueName = generateUniqueName(name);
		auto createdGO = std::make_shared<GameObject>();
		createdGO->m_name = uniqueName;
		
		m_gameObjectMap[uniqueName] = createdGO;
		createdGO->SetSelfPointer(createdGO);

		return createdGO;
	}


	void Destroy(const std::string& name)
	{
		m_gameObjectMap.erase(name);
	}

	void Destroy(std::shared_ptr<GameObject> go)
	{
		m_gameObjectMap.erase(go->m_name);
	}


protected:
	/// <summary>
	/// Generates a uniquename if the name already exists e.g if there is already a player it becomes player(1)
	/// </summary>
	/// <param name="name"></param>
	/// <returns></returns>
	std::string generateUniqueName(const std::string& name)
	{
		std::string modifiedName = name;
		int count = m_gameObjectMap.count(modifiedName);
		int Counter = 0;

		while (count > 0) {
			modifiedName = name + "(" + std::to_string(Counter++) + ")";
			count = m_gameObjectMap.count(modifiedName);

		}

		return modifiedName;
	}

	
	
};

