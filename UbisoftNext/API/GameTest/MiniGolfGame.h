#pragma once
#include "Game.h"
#include "Grid.h"

class MiniGolfGame :
    public Game
{
public:
	MiniGolfGame();
	~MiniGolfGame() override;
	void InternalInit() override;
	void InternalUpdate(const float deltaTime) override;
	void InternalRender() override;
	void InternalShutdown() override;

	GRID::GridSystem* GetGridSystem() override;
private:
	GRID::GridSystem m_grid_system_;
};

