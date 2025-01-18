#pragma once
#include "CustomMath.h"
#include <unordered_map>
#include <memory> // For smart pointers
#include <vector>
#include <array>
namespace GRID
{
    struct Cell
    {
    public:
        Cell(IntVector2 gridPosition,bool isObstacle) : m_gridPosition(gridPosition), m_isObstacle(false), m_gCost(0), m_hCost(0) {
         
        }
        Cell() : m_gridPosition(IntVector2(0,0)), m_isObstacle(false), m_gCost(0), m_hCost(0) {}

        int GetFCost() const
        {
            return m_gCost + m_hCost;
        }

        bool operator==(const Cell& other) const
        {
            return m_gridPosition == other.m_gridPosition &&
                m_isObstacle == other.m_isObstacle &&
                m_gCost == other.m_gCost &&
                m_hCost == other.m_hCost;
               // m_parentGridPosition == other.m_parentGridPosition;
        }


    public:
        bool m_isObstacle;
        IntVector2 m_gridPosition;
        Vector2 m_worldPosition;
        int m_gCost;
        int m_hCost;
        Cell* m_parentCell;
    };

    class GridSystem
    {
    public:
        GridSystem(int cellSize = 50, Vector2 origin = Vector2(0, 0), IntVector2 gridSize = IntVector2(50, 50))
            : m_cellSize(cellSize), m_origin(origin), m_gridSize(gridSize)
        {
            CreateGrid();
        }

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

        void SetObstacle(Vector2 worldPosition);


        Cell* GetCell(IntVector2 gridPosition);

        Cell* GetCellFromWorldPosition(Vector2 worldPosition);



        std::vector<Cell*> GetNeighbours(Cell* cell);
    
        std::vector<Vector2> GetAllFilledCells();
    
    
    private:
        void CreateGrid();

    public:
        IntVector2 m_gridSize;
    private:
        int m_cellSize;
      
        Vector2 m_origin;
        std::vector<std::vector<Cell>> m_grid;
        std::unordered_map<IntVector2, Vector2> m_filled_cells;
    };

};
