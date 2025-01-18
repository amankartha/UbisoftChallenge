#include "stdafx.h"
#include "Grid.h"
#include <memory>
#include <algorithm>
IntVector2 GRID::GridSystem::WorldToGrid(Vector2 worldPosition) const
{
	Vector2 centeredOrigin = m_origin - Vector2(m_gridSize.x * m_cellSize / 2.0f, m_gridSize.y * m_cellSize / 2.0f);

	int gridX = (int)std::floor((worldPosition.x - centeredOrigin.x) / m_cellSize);
	int gridY = (int)std::floor((worldPosition.y - centeredOrigin.y) / m_cellSize);

	gridX = std::clamp(gridX, 0, m_gridSize.x - 1);
	gridY = std::clamp(gridY, 0, m_gridSize.y - 1);

	return IntVector2(gridX, gridY);
}

Vector2 GRID::GridSystem::GridToWorld(IntVector2 gridPosition) const
{
	Vector2 centeredOrigin = m_origin - Vector2(m_gridSize.x * m_cellSize / 2.0f, m_gridSize.y * m_cellSize / 2.0f);

	return Vector2(
		centeredOrigin.x + gridPosition.x * m_cellSize + m_cellSize / 2,
		centeredOrigin.y + gridPosition.y * m_cellSize + m_cellSize / 2
	);
}

void GRID::GridSystem::SetObstacle(IntVector2 gridPosition)
{
	m_grid[gridPosition.x][gridPosition.y].m_isObstacle = true;
	m_filled_cells[gridPosition] = Vector2(GridToWorld(gridPosition));
}

void GRID::GridSystem::SetObstacle(Vector2 worldPosition)
{
	IntVector2 gridPos = WorldToGrid(worldPosition);

	m_grid[gridPos.x][gridPos.y].m_isObstacle = true;
	m_filled_cells[gridPos] = Vector2(GridToWorld(gridPos));
}

void GRID::GridSystem::RemoveObstacle(IntVector2 gridPosition)
{

	if (m_filled_cells.contains(gridPosition))
	{
		m_filled_cells.erase(gridPosition);
	}
	GetCell(gridPosition)->m_isObstacle = false;
}

void GRID::GridSystem::RemoveObstacle(Vector2 worldPosition)
{
	IntVector2 gridPos = WorldToGrid(worldPosition);
	if (m_filled_cells.contains(gridPos))
	{
		m_filled_cells.erase(gridPos);
	}
	GetCell(gridPos)->m_isObstacle = false;
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

std::vector<Vector2> GRID::GridSystem::GetAllFilledCells() const
{
	std::vector<Vector2> filledCellsWorldPositions;
	filledCellsWorldPositions.reserve(m_filled_cells.size());
	for (auto kv : m_filled_cells)
	{
		filledCellsWorldPositions.push_back(kv.second);
	}
	return filledCellsWorldPositions;
}

std::vector<IntVector2> GRID::GridSystem::GetAllFillCellsGridPositions() const
{
	std::vector<IntVector2> gridpositions;
	gridpositions.reserve(m_filled_cells.size());
	for (auto kv : m_filled_cells)
	{
		gridpositions.push_back(kv.first);
	}
	return gridpositions;
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
