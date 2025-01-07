#include "stdafx.h"
#include "GameObjectManager.h"

GameObject& GameObjectManager::Create(const std::string& name)
{
	std::string uniqueName = generateUniqueName(name);
	auto createdGO = std::make_unique<GameObject>();
	m_gameObjectMap[uniqueName] = std::move(createdGO);
	m_gameObjectMap[uniqueName]->m_name = uniqueName;
	m_gameObjectMap[uniqueName]->AddComponent<Ctransform>();

	return *m_gameObjectMap[uniqueName].get();
   
}

std::string GameObjectManager::generateUniqueName(const std::string& name)
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
