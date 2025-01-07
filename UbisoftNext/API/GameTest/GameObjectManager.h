#pragma once
#include <unordered_map>
#include "GameObject.h"
#include "DataStructure.h"

class GameObjectManager
{
public:
	GameObjectManager() {
		m_gameObjectMap.reserve(500);
	}
	~GameObjectManager() = default;

	GameObject& Create(const std::string& name);


	void Destroy(const std::string& name)
	{
		m_gameObjectMap.erase(name);
	}

	void Destroy(std::shared_ptr<GameObject> go)
	{
		m_gameObjectMap.erase(go->m_name);
	}
	GameObject* Find(std::string name)
	{
		auto it = m_gameObjectMap.find(name);
		if (it != m_gameObjectMap.end())
		{
			return it->second.get(); 
		}
	}
	void InitAll()
	{
		for (auto& it : m_gameObjectMap) {

			it.second->Init();
		}
	}
	void UpdateAll()
	{
		for (auto& it : m_gameObjectMap) {

			it.second->Update();
		}
	}
private:
	std::string generateUniqueName(const std::string& name);

private:

	std::unordered_map<std::string, std::unique_ptr<GameObject>> m_gameObjectMap;
};

