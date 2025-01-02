#pragma once
#include "Grid.h"
class Vector2;

class Pathfinding
{

public:

	Pathfinding(GRID::GridSystem gridSystem) : m_grid(gridSystem) {}

	std::vector<IntVector2> FindPath(Vector2 startPos, Vector2 endPos);

private:
	std::vector<IntVector2> ReTracePath(GRID::Cell StartCell, GRID::Cell endCell,std::vector<GRID::Cell> cells);

private:
	GRID::GridSystem& m_grid;


};

