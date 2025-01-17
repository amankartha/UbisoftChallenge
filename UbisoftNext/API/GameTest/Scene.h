#pragma once
#include <vector>

class Game;

class Scene
{
public:
	Scene(Game* GameInstance);
	~Scene();
	void SwitchToScene();
	void AddGameObject(int gameObjectID);
	void RemoveGameObject(int gameObjectID);
	void DestroyScene();

private:
	std::vector<int> m_gameObjects_in_scene_;
};

