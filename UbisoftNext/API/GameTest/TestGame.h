#pragma once

#include "Game.h"
#include "Grid.h"


class TestGame :
    public Game
{

public:
	 void InternalInit() override;
	 void InternalUpdate(const float deltaTime) override;
	 void InternalRender() override;
	 void InternalShutdown() override;
private:
	GRID::GridSystem m_gridSystem;

};

