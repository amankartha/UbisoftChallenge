#pragma once
#include <vector>
#include "CustomMath.h"



namespace PHYSICS
{

	class Body
	{

		std::vector<Cell*> currentCells;

		std::vector<Body*> GetNearbyBodies()
		{
			std::vector<Body*> result;
			for (auto& c : currentCells)
			{
				for (auto& b : c->GetBodies())
				{
					result.push_back(b);
				}
			}
			return result;
		}
	};

	class Cell
	{
		AABB cellBounds;
		std::vector<Collider*> bodies;
		void AddCell(Collider* body);
		void RemoveCell(Collider* body);
	};

	class Grid
	{


	private:
		std::vector<std::vector<Cell*>> cells;
		int cellWidth, cellHeight;
	public:
		Grid(int width, int height) :cellWidth(width), cellHeight(height) {}


		Cell* GetCell(int x, int y);

		Vector2 GetIndex(Vector2 position);

	};
};

