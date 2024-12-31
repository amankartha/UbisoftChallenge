#pragma once
#include "CustomMath.h"
#include <vector>
#include <unordered_map>
namespace GRID
{
	struct Cell
	{
	public:
		bool isObstacle;
	};

	class GridSystem
	{
	public:
		GridSystem(float cellSize = 50.0, Vector2 origin = Vector2(0,0))
			: m_cellSize(cellSize), m_origin(origin) {}

		Vector2 GetOrigin() const
		{
			return m_origin;
		}
		int GetCellSize() const
		{
			return m_cellSize;
		}

		IntVector2 WorldToGrid(Vector2 worldPosition) const;
		
		Vector2 GridToWorld(IntVector2 gridPosition) const;

		void SetObstacle(IntVector2 gridPosition);
		
		void AddCell(IntVector2 gridPosition, bool isObstacle);
		
		Cell* GetCell(IntVector2 gridPosition);
		
		bool CellExists(IntVector2 gridPosition);


	private:
		int m_cellSize;
		Vector2 m_origin;
		std::unordered_map<IntVector2, Cell> m_grid;
	};

};

