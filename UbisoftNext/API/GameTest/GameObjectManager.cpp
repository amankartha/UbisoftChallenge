#include "stdafx.h"
#include "GameObjectManager.h"

GameObject& GameObjectManager::Create(const std::string& name)
{
	std::string uniqueName = generateUniqueName(name);
	auto& createdGO = m_gameObjectMap[uniqueName];
	createdGO.m_name = uniqueName;
	m_gameObjectMap[uniqueName] = createdGO;
	

	return createdGO;
   
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
