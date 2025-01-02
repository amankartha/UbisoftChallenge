#include "stdafx.h"
#include "Pathfinding.h"
#include "Grid.h"
#include "cmath"
#include <vector>
#include <unordered_set>


//----------------------------------------------------------------------
//Helper Functions
//----------------------------------------------------------------------



std::vector<GRID::Cell*> Pathfinding::ReTracePath(GRID::Cell* startCell, GRID::Cell* endCell)
{
	std::vector<GRID::Cell*> path;
	GRID::Cell* currentCell = endCell;

	while (currentCell != startCell)
	{
		path.push_back(currentCell);
		currentCell = currentCell->m_parentCell;
	}

	std::reverse(path.begin(), path.end());

	return path;
}

int GetDistance(GRID::Cell* A, GRID::Cell* B) //manhattan distance
{
	int distance_x = std::abs(A->m_gridPosition.x - B->m_gridPosition.x);
	int distance_y = std::abs(A->m_gridPosition.y - B->m_gridPosition.y);

	if (distance_x > distance_y)
	{
		return 14 * distance_y + 10 * (distance_x - distance_y);
	}
	else
	{
		return 14 * distance_x + 10 * (distance_y - distance_x);
	}
}
//----------------------------------------------------------------------
// Functions
//----------------------------------------------------------------------


std::vector<GRID::Cell*> Pathfinding::FindPath(Vector2 startPos, Vector2 endPos)
{


	

	GRID::Cell* startCell = m_grid.GetCellFromWorldPosition(startPos);
	GRID::Cell* endCell = m_grid.GetCellFromWorldPosition(endPos);

	//Return out if endPos is an Obstacle for now
	if (endCell->m_isObstacle)
	{
		std::vector<GRID::Cell*> empty;
		return  empty;
	}


	
	std::vector<GRID::Cell*> openSet;
	std::unordered_set<GRID::Cell*> closedSet;

	openSet.push_back(startCell);


	while(openSet.size() >  0)
	{
		GRID::Cell* currentNode = openSet[0];

		for (int i = 1; i < openSet.size(); i++)
		{
			if (openSet[i]->GetFCost() < currentNode->GetFCost() ||
				(openSet[i]->GetFCost() == currentNode->GetFCost() && openSet[i]->m_hCost < currentNode->m_hCost))
			{
				currentNode = openSet[i];
			}
		}

		openSet.erase(find(openSet.begin(),openSet.end(),currentNode));
		closedSet.insert(currentNode);

		if (currentNode == endCell)
		{
		  return  ReTracePath(startCell, endCell);
			
		}

		for (auto neighbour : m_grid.GetNeighbours(currentNode))
		{
			if (neighbour->m_isObstacle || 
				closedSet.find(neighbour) != closedSet.end())
			{
				continue;
			}

			int newMovementCostToNeighbour = currentNode->m_gCost + GetDistance(currentNode, neighbour);

			if (newMovementCostToNeighbour < neighbour->m_gCost || std::find(openSet.begin(), openSet.end(), neighbour) == openSet.end())
			{
				neighbour->m_gCost = newMovementCostToNeighbour;
				neighbour->m_hCost = GetDistance(neighbour, endCell);
				
				neighbour->m_parentCell = currentNode;

				if (std::find(openSet.begin(), openSet.end(), neighbour) == openSet.end())
				{
					openSet.push_back(neighbour);
				}
			}
		}

	}
}
