#include "stdafx.h"
#include "GameObjectManager.h"


#include "appUtility.h"
#include "Gameobject.h"


void GameObjectManager::AddToLookupTable(std::string name, int id)
{
	while (m_lookupTable.find(name) != m_lookupTable.end())
	{
		name = name + "+";
	}
	m_lookupTable[name] = id;
}

int GameObjectManager::SearchTable(std::string name)
{
	if (m_lookupTable.find(name) == m_lookupTable.end())
	{
		return -1;
	}
	else
	{
		return m_lookupTable[name];
	}
}


void GameObjectManager::Destroy(int ID)
{
	m_idsToDestroy.push_back(ID);
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

GameObject* GameObjectManager::FindUsingTable(std::string name)
{
	int id = SearchTable(name);
	if (id  == -1 )
	{
		return nullptr;
	}
	
	return Find(id);
}

void GameObjectManager::InitAll()
{
	for (auto& it : m_gameObjectMap) {

		it.second->Init();
	}
}

void GameObjectManager::UpdateAll(float deltaTime)
{
	for (auto& it : m_gameObjectMap) {

		it.second->Update(deltaTime);
	}
}

void GameObjectManager::CleanUpAndDelete()
{
	for (int ID : m_idsToDestroy)
	{
		m_gameObjectMap.erase(ID);
		
	}
	m_idsToDestroy.clear();
}

void GameObjectManager::RenderAll()
{
	for (auto& it : m_gameObjectMap) {

		it.second->Render();
	}
}

int GameObjectManager::GetNumberOfGameObjects() const
{
	return m_gameObjectMap.size();
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
