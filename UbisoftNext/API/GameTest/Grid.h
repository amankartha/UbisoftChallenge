#pragma once
#include "CustomMath.h"
#include <unordered_map>
#include <memory> // For smart pointers
#include <vector>
#include <array>

#include "ObserverPattern.h"
#include "Renderer.h"

namespace GRID
{
    struct Cell
    {
    public:
        Cell(IntVector2 gridPosition,bool isObstacle) : m_gridPosition(gridPosition), m_isObstacle(false), m_isPlaceable(true), m_gCost(0), m_hCost(0) {
         
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
        bool m_isPlaceable;

        IntVector2 m_gridPosition;
        Vector2 m_worldPosition;
        int m_gCost;
        int m_hCost;
        Cell* m_parentCell;
    };


    class GridSystem : public Events::IPatternSubject
    {
    public:
        GridSystem(int cellSize = 50, Vector2 origin = Vector2(0, 0), IntVector2 gridSize = IntVector2(100, 100))
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

        void RemoveObstacle(IntVector2 gridPosition);

        void RemoveObstacle(Vector2 worldPosition);
        void RemovePlaceAble(IntVector2 gridPosition);
        void RemovePlaceAble(Vector2 worldPosition);

        Cell* GetCell(IntVector2 gridPosition);

        Cell* GetCellFromWorldPosition(Vector2 worldPosition);

        std::vector<Cell*> GetNeighbours(Cell* cell);
    
        std::vector<Vector2> GetAllFilledCells() const;
    
        std::vector<IntVector2> GetAllFillCellsGridPositions() const;

        std::vector<uint64_t> ConvertPatternToHashes(const std::vector<std::vector<int>>& pattern);

    	std::pair<bool,std::vector<IntVector2>> MatchPatternsAroundNewCell(const std::vector<std::vector<int>>& pattern, IntVector2 center, bool clear = false);

        std::vector<std::vector<std::vector<int>>> GenerateAllRotations(const std::vector<std::vector<int>>& pattern); //basically returns a vector of matrices, looks scarier than it is

    	void UpdateRowHash(int row);

        std::vector<std::vector<int>> Rotate90(const std::vector<std::vector<int>>& pattern);

        void CreateGrid();
        void ClearCells(std::vector<IntVector2> cells);
        void ClearPlaceAble(std::vector<IntVector2> cells);

    public:
        IntVector2 m_gridSize;
        bool isFound = false;
    private:
        int m_cellSize;
      
        Vector2 m_origin;
        std::vector<std::vector<Cell>> m_grid;
        std::unordered_map<IntVector2, Vector2> m_filled_cells;
        std::vector<uint64_t> m_rowHash_;

    };




};
