#include "stdafx.h"
#include "Grid.h"


namespace PHYSICS
{
    Cell* Grid::GetCell(int x, int y)
    {
        return cells[x][y];
    }

    Vector2 Grid::GetIndex(Vector2 position)
    {
        return { position.x / cellWidth,position.y / cellHeight };
    }
    void Cell::AddCell(Collider* body)
    {
    }
    void Cell::RemoveCell(Collider* body)
    {
    }
};
