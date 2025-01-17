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

		auto createdGO = std::make_unique<T>(GetGameInstance(), std::forward<Args>(args)...);
		int id = GenerateID();
		m_gameObjectMap[id] = std::move(createdGO);
		m_gameObjectMap[id]->m_name = name;
		m_gameObjectMap[id]->AddComponent<Ctransform>();
		App::PrintOutputMessage("GameObject " + name + " Created\n");
		return id;
	}


	void Destroy(int ID);

	//void Destroy(std::shared_ptr<GameObject> go);

	GameObject* Find(int ID);

	void InitAll();

	void UpdateAll();

	int GetNumberOfGameObjects() const;

private:
	std::string generateUniqueName(const std::string& name);

private:
	std::unordered_map<int, std::unique_ptr<GameObject>> m_gameObjectMap;

};

