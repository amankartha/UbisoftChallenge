#include "stdafx.h"
#include "Grid.h"

IntVector2 GRID::GridSystem::WorldToGrid(Vector2 worldPosition) const
{
	return IntVector2((worldPosition.x - m_origin.x) / m_cellSize, (worldPosition.y - m_origin.y / m_cellSize));
}

Vector2 GRID::GridSystem::GridToWorld(IntVector2 gridPosition) const
{
	return Vector2((m_origin.x + gridPosition.x * m_cellSize + m_cellSize/2),(m_origin.y + gridPosition.y * m_cellSize + m_cellSize / 2));
}

void GRID::GridSystem::SetObstacle(IntVector2 gridPosition)
{
	if (m_grid.find(gridPosition) != m_grid.end())
	{
		m_grid[gridPosition].isObstacle = true;
	}

}

void GRID::GridSystem::AddCell(IntVector2 gridPosition, bool isObstacle)
{
	m_grid[gridPosition] = { isObstacle };
}

GRID::Cell* GRID::GridSystem::GetCell(IntVector2 gridPosition)
{
	auto it = m_grid.find(gridPosition);

	if (it != m_grid.end())
	{
		return &it->second;
	}
	return nullptr;

}

bool GRID::GridSystem::CellExists(IntVector2 gridPosition)
{
	return m_grid.find(gridPosition) != m_grid.end();
}
