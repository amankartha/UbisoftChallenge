#pragma once
#include <unordered_map>
#include "GameObject.h"
#include "DataStructure.h"

class GameObjectManager
{
public:
	GameObjectManager() {
		m_gameObjects.Init(2000);
	}
	~GameObjectManager()
	{
		m_gameObjects.Dispose();
	}

	GameObject& Create(const std::string& name);


	/*void Destroy(const std::string& name)
	{
		m_gameObjects.Free(name);
	}*/

	void Destroy(GameObject& go)
	{
		m_gameObjects.Free(go);
	}
	GameObject* Find(int ID)
	{
		return m_gameObjects.TryToGet(ID);
	}
	//GameObject& Find(std::string name)
	//{
	//	auto it = m_gameObjects.find(name);
	//	if (it != m_gameObjects.end())
	//	{
	//		return it->second;
	//	}
	//}

	void InitAll()
	{
		GameObject* GO;
		while (m_gameObjects.Next(GO)) {

			GO->Init();
		}
	}
	void UpdateAll()
	{
		GameObject* GO;
		while (m_gameObjects.Next(GO)) {

			GO->Update();
		}
	}
private:
	std::string generateUniqueName(const std::string& name);

private:

	DataArray<GameObject> m_gameObjects;  //Storage of all Gameobjects
};

