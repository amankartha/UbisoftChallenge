#pragma once
#include <unordered_map>
#include <memory>
#include <string>

#include "IIDSystem.h"
class GameObject;

class GameObjectManager : public IIDSystem
{
public:
	GameObjectManager();
	~GameObjectManager();

	GameObject& Create(const std::string& name);


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

