#include "stdafx.h"
#include "Grid.h"
#include <memory>

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
		m_grid[gridPosition]->m_isObstacle = true;
	}

}

void GRID::GridSystem::AddCell(IntVector2 gridPosition, bool isObstacle)
{
	if (GetCell(gridPosition))
	{
		return;
	}
	else
	{
		m_grid[gridPosition] = std::make_shared<Cell>(gridPosition,isObstacle);
	}
}

std::shared_ptr<GRID::Cell> GRID::GridSystem::GetCell(IntVector2 gridPosition)
{
	auto it = m_grid.find(gridPosition);

	if (it != m_grid.end())
	{
		return it->second;
	}
	return nullptr;

}

GRID::Cell GRID::GridSystem::GetCellFromWorldPosition(Vector2 worldPosition)
{
	return *GetCell(WorldToGrid(worldPosition));
}

bool GRID::GridSystem::CellExists(IntVector2 gridPosition)
{
	return m_grid.find(gridPosition) != m_grid.end();
}

std::array<GRID::Cell, 8>& GRID::GridSystem::GetNeighbours(IntVector2 gridPosition)
{
	int count = 0;
	for (int x = -1; x <= 1; x++)
	{
		for (int y = -1; y <= 1; y++)
		{
			if (x == 0 && y == 0)
			{
				continue;
			}
			

			if (CellExists(IntVector2(x, y)))   //if cell exists you push back the cell if not create a temp cell to hold cost values and push that
			{

				m_neighbourGrid[count] = *GetCell(IntVector2(gridPosition.x + x,gridPosition.y + y));
				count++;
			}
			else
			{
				m_neighbourGrid[count] = Cell(IntVector2(gridPosition.x + x,gridPosition.y + y), false);
				count++;
			}
		}

	}

	return m_neighbourGrid;
}

//std::vector<GRID::Cell*> GRID::GridSystem::GetNeighbours(Cell* cell)
//{
//	std::vector<Cell*> neighbours;
//
//	for (int x = -1; x <= 1; x++)
//	{
//		for (int y = -1; y <= 1; y++)
//		{
//			if (x == 0 && y == 0)
//			{
//				continue;
//			}
//			
//
//			if (CellExists(IntVector2( x, y)))   //if cell exists you push back the cell if not create a temp cell to hold cost values and push that
// 			{
//
//				neighbours.push_back(GetCell(IntVector2(x, y)));
//			}
//			else
//			{
//				neighbours.push_back(&Cell(IntVector2(x, y)));
//			}
//		}
//
//	}
//
//	return neighbours;
//}
