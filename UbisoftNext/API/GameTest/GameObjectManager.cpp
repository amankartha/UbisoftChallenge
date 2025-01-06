#include "stdafx.h"
#include "GameObjectManager.h"

GameObject& GameObjectManager::Create(const std::string& name)
{
	//std::string uniqueName = generateUniqueName(name);

	GameObject& createdGO = m_gameObjects.Alloc();
	createdGO.m_name = name;

	

	return createdGO;
   
}

//std::string GameObjectManager::generateUniqueName(const std::string& name)
//{
//	std::string modifiedName = name;
//	int count = 0;
//	int Counter = 0;
//	GameObject* GO;
//	while (m_gameObjects.Next(GO) ) {
//		co
//	}
//	modifiedName = name + "(" + std::to_string(Counter++) + ")";
//	count = m_gameObjects.count(modifiedName);
//	return modifiedName;
//}
