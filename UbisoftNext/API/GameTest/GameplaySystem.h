#pragma once

class Game;

class GameplaySystem
{
public:
	GameplaySystem(Game* gameinstance) : GameInstance(gameinstance) {}
	 ~GameplaySystem() = default;


	 Game* GetGameInstance() { return GameInstance; }
private:
	Game* GameInstance;
};
