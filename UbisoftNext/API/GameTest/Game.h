#pragma once
#include "PhysicsSimulation.h"
#include <memory>
#include "Renderer.h"
#include "GameObject.h"
class Game
{
protected:
	std::unique_ptr<PHYSICS::PhysicsSimulation> m_physicsSimulation;
	std::unique_ptr<Renderer> m_renderer;
	std::unordered_map<std::string, std::shared_ptr<GameObject>> GAMEOBJECTSMAP;
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



	std::shared_ptr<GameObject> Create(const std::string& name)
	{
		std::string uniqueName = generateUniqueName(name);
		auto createdGO = std::make_shared<GameObject>();
		createdGO->m_name = uniqueName;
		
		GAMEOBJECTSMAP[uniqueName] = createdGO;
		createdGO->SetSelfPointer(createdGO);

		return createdGO;
	}
	void Destroy(const std::string& name)
	{
		GAMEOBJECTSMAP.erase(name);
	}
	void Destroy(std::shared_ptr<GameObject> go)
	{
		GAMEOBJECTSMAP.erase(go->m_name);
	}


protected:
	std::string generateUniqueName(const std::string& name)
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

	
	
};

