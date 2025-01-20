#pragma once
#include <unordered_map>
#include <memory>
#include <string>

#include "appUtility.h"
#include "GameplaySystem.h"
#include "IIDSystem.h"
#include "GameObject.h"
#include "ObjectPool.h"

class GameObjectManager : public GameplaySystem, public IIDSystem
{
public:
	GameObjectManager(Game* gameinstance): GameplaySystem(gameinstance)
	{
		m_gameObjectMap.reserve(1000);
	}

	~GameObjectManager() = default;

	//int Create(const std::string& name);
	//
	//int GameObjectManager::Create(const std::string& name)
	//{
	//	//std::string uniqueName = generateUniqueName(name);
	//	auto createdGO = std::make_unique<GameObject>(GetGameInstance());
	//	int id = GenerateID();
	//	m_gameObjectMap[id] = std::move(createdGO);
	//	m_gameObjectMap[id]->m_name = name;
	//	m_gameObjectMap[id]->AddComponent<Ctransform>();
	//	App::PrintOutputMessage("GameObject " + name + " Created\n");
	//	return id;

	//}

	template <typename T, typename... Args>
	int Create(const std::string& name, Args&&... args) {
		static_assert(std::is_base_of<GameObject, T>::value, "T must be derived from GameObject");
		int id = GenerateID();
		auto createdGO = std::make_unique<T>(GetGameInstance(),id, std::forward<Args>(args)...);
	
		m_gameObjectMap[id] = std::move(createdGO);
		m_gameObjectMap[id]->m_name = name;
		m_gameObjectMap[id]->AddComponent<Ctransform>();
		m_gameObjectMap[id]->Init();
		App::PrintOutputMessage("GameObject " + name + " Created\n");
		return id;
	}

	template <typename T, typename... Args>
	int CreateAndAddToLookUpTable(const std::string& name, Args&&... args)
	{
		static_assert(std::is_base_of<GameObject, T>::value, "T must be derived from GameObject");
		int id = GenerateID();
		auto createdGO = std::make_unique<T>(GetGameInstance(), id, std::forward<Args>(args)...);

		m_gameObjectMap[id] = std::move(createdGO);
		m_gameObjectMap[id]->m_name = name;
		m_gameObjectMap[id]->AddComponent<Ctransform>();
		m_gameObjectMap[id]->Init();
		App::PrintOutputMessage("GameObject " + name + " Created\n");
		AddToLookupTable(name,id);

		return id;
	}
	
	void AddToLookupTable(std::string name,int id);

	//returns -1 if not found
	int SearchTable(std::string name);

	void Destroy(int ID);

	//void Destroy(std::shared_ptr<GameObject> go);

	GameObject* Find(int ID);

	GameObject* FindUsingTable(std::string name);

	void InitAll();

	void UpdateAll(float deltaTime);

	void CleanUpAndDelete();

	void RenderAll();

	int GetNumberOfGameObjects() const;

public:
	std::unordered_map<std::string, int> m_lookupTable;
private:
	std::string generateUniqueName(const std::string& name);
	
private:
	std::unordered_map<int, std::unique_ptr<GameObject>> m_gameObjectMap;
	std::vector<int> m_idsToDestroy;
	

};



