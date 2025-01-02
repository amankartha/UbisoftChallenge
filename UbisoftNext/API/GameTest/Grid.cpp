#include "stdafx.h"
#include "Grid.h"
#include <memory>
#include <algorithm>
IntVector2 GRID::GridSystem::WorldToGrid(Vector2 worldPosition) const
{
	int gridX = (int)std::floor((worldPosition.x - m_origin.x) / m_cellSize);
	int gridY = (int)std::floor((worldPosition.y - m_origin.y) / m_cellSize);

	gridX = std::clamp(gridX, 0, m_gridSize.x - 1);
	gridY = std::clamp(gridY, 0, m_gridSize.y - 1);

	return IntVector2(gridX, gridY);
}

Vector2 GRID::GridSystem::GridToWorld(IntVector2 gridPosition) const
{
	return Vector2((m_origin.x + gridPosition.x * m_cellSize + m_cellSize/2),(m_origin.y + gridPosition.y * m_cellSize + m_cellSize / 2));
}

void GRID::GridSystem::SetObstacle(IntVector2 gridPosition)
{
	m_grid[gridPosition.x][gridPosition.y].m_isObstacle = true;

}

//returns null_ptr if cell does not exist
GRID::Cell* GRID::GridSystem::GetCell(IntVector2 gridPosition)
{
	return  &m_grid[gridPosition.x][gridPosition.y];

}

GRID::Cell* GRID::GridSystem::GetCellFromWorldPosition(Vector2 worldPosition)
{
	
	return GetCell(WorldToGrid(worldPosition));
	
}


std::vector<GRID::Cell*> GRID::GridSystem::GetNeighbours(GRID::Cell* cell)
{
	std::vector<GRID::Cell*> cells;
	for (int x = -1; x <= 1; x++)
	{
		for (int y = -1; y <= 1; y++)
		{
			if (x == 0 && y == 0)
			{
				continue;
			}
			

			int checkX = cell->m_gridPosition.x + x;
			int checkY = cell->m_gridPosition.y + y;

			if (checkX >= 0 && checkX < m_gridSize.x && checkY >= 0 && checkY < m_gridSize.y) {

				cells.push_back(GetCell(IntVector2(checkX, checkY)));
			}
		
		}

	}

	return cells;
}

void GRID::GridSystem::CreateGrid()
{
	m_grid.resize(m_gridSize.y, std::vector<Cell>(m_gridSize.x));

	for (int x = 0; x < m_gridSize.x; x++) {
		for (int y = 0; y < m_gridSize.y; y++) {
			m_grid[x][y] = Cell(IntVector2(x, y), false);
			m_grid[x][y].m_worldPosition = GridToWorld(IntVector2(x, y));
		}
	}

}
