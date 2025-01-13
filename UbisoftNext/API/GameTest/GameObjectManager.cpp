#include "stdafx.h"
#include "GameObjectManager.h"
#include "Gameobject.h"



void GameObjectManager::Destroy(int ID)
{
	m_gameObjectMap.erase(ID);
}

//void GameObjectManager::Destroy(std::shared_ptr<GameObject> go)
//{
//	m_gameObjectMap.erase(go->m_name);
//}

GameObject* GameObjectManager::Find(int ID)
{
	auto it = m_gameObjectMap.find(ID);
	if (it != m_gameObjectMap.end())
	{
		return it->second.get(); 
	}

	return nullptr;
}

void GameObjectManager::InitAll()
{
	for (auto& it : m_gameObjectMap) {

		it.second->Init();
	}
}

void GameObjectManager::UpdateAll()
{
	for (auto& it : m_gameObjectMap) {

		it.second->Update();
	}
}

int GameObjectManager::GetNumberOfGameObjects() const
{
	return m_gameObjectMap.size();
}

GameObject& GameObjectManager::Create(const std::string& name)
{
	//std::string uniqueName = generateUniqueName(name);
	auto createdGO = std::make_unique<GameObject>(GetGameInstance());
	int id = GenerateID();
	m_gameObjectMap[id] = std::move(createdGO);
	m_gameObjectMap[id]->m_name = name;
	m_gameObjectMap[id]->AddComponent<Ctransform>();

	return *m_gameObjectMap[id].get();
   
}

//std::string GameObjectManager::generateUniqueName(const std::string& name)
//{
//	std::string modifiedName = name;
//	int count = m_gameObjectMap.count(modifiedName);
//	int Counter = 0;
//
//	while (count > 0) {
//		modifiedName = name + "(" + std::to_string(Counter++) + ")";
//		count = m_gameObjectMap.count(modifiedName);
//
//	}
//
//	return modifiedName;
//}
