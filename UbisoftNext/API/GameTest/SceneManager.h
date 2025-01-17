#pragma once
#include <vector>
#include "Scene.h"

class Game;

class SceneManager
{
public:
	SceneManager(Game* instance);
	~SceneManager();
	void SwitchToScene();
	int AddScene(Scene scene);
	void LoadScene(int Scene);
private:
	std::vector<Scene> m_scenes_;
};

