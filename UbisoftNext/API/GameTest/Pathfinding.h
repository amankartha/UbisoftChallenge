#pragma once
#include "Grid.h"
struct Vector2;


class Pathfinding
{

public:

	Pathfinding(GRID::GridSystem& gridSystem) : m_grid(gridSystem) {}

	std::vector<GRID::Cell*> FindPath(Vector2 startPos, Vector2 endPos);

private:

	std::vector<GRID::Cell*> ReTracePath(GRID::Cell* StartCell, GRID::Cell* endCell);

private:
	GRID::GridSystem& m_grid;


};

