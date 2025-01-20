#include "stdafx.h"
#include "Grid.h"
#include <memory>
#include <algorithm>

IntVector2 GRID::GridSystem::WorldToGrid(Vector2 worldPosition) const
{
    Vector2 centeredOrigin = m_origin - Vector2(m_gridSize.x * m_cellSize / 2.0f, m_gridSize.y * m_cellSize / 2.0f);

    int gridX = static_cast<int>(std::floor((worldPosition.x - centeredOrigin.x) / m_cellSize));
    int gridY = static_cast<int>(std::floor((worldPosition.y - centeredOrigin.y) / m_cellSize));

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
    if (gridPosition.x >= 0 && gridPosition.y >= 0 &&
        gridPosition.x < m_gridSize.x && gridPosition.y < m_gridSize.y)
    {
        m_grid[gridPosition.x][gridPosition.y].m_isObstacle = true;
        m_filled_cells[gridPosition] = GridToWorld(gridPosition);
        UpdateRowHash(gridPosition.y);
        NotifyObservers(Events::PatternEventType::base,gridPosition);
      // isFound |=  MatchPatternsAroundNewCell({ {1,1,1} ,{0,0,0},{1,1,1} }, gridPosition,true).first;
    }
}

void GRID::GridSystem::SetObstacle(Vector2 worldPosition)
{
    SetObstacle(WorldToGrid(worldPosition));
    UpdateRowHash(WorldToGrid(worldPosition).y);
    NotifyObservers(Events::PatternEventType::base, WorldToGrid(worldPosition));
   // isFound |=  MatchPatternsAroundNewCell({ {1,1,1} ,{1,0,1},{1,1,1} }, WorldToGrid(worldPosition),true).first;
}

void GRID::GridSystem::RemoveObstacle(IntVector2 gridPosition)
{
    if (m_filled_cells.contains(gridPosition))
    {
        m_filled_cells.erase(gridPosition);
        GetCell(gridPosition)->m_isObstacle = false;
        UpdateRowHash(gridPosition.y);
    }
}

void GRID::GridSystem::RemoveObstacle(Vector2 worldPosition)
{
    RemoveObstacle(WorldToGrid(worldPosition));
}

GRID::Cell* GRID::GridSystem::GetCell(IntVector2 gridPosition)
{
    if (gridPosition.x < 0 || gridPosition.y < 0 ||
        gridPosition.x >= m_gridSize.x || gridPosition.y >= m_gridSize.y)
    {
        return nullptr;
    }
    return &m_grid[gridPosition.x][gridPosition.y];
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

            if (checkX >= 0 && checkX < m_gridSize.x && checkY >= 0 && checkY < m_gridSize.y)
            {
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
    for (const auto& kv : m_filled_cells)
    {
        filledCellsWorldPositions.push_back(kv.second);
    }
    return filledCellsWorldPositions;
}

std::vector<IntVector2> GRID::GridSystem::GetAllFillCellsGridPositions() const
{
    std::vector<IntVector2> gridpositions;
    gridpositions.reserve(m_filled_cells.size());
    for (const auto& kv : m_filled_cells)
    {
        gridpositions.push_back(kv.first);
    }
    return gridpositions;
}

std::vector<uint64_t> GRID::GridSystem::ConvertPatternToHashes(const std::vector<std::vector<int>>& pattern) //unused unfortunately but I see potential in this
{
    std::vector<uint64_t> hashPattern(pattern.size());
    for (size_t row = 0; row < pattern.size(); ++row)
    {
        uint64_t hash = 0;
        for (int cell : pattern[row])
        {
            hash = (hash << 1) | cell;
        }
        hashPattern[row] = hash;
    }
    return hashPattern;
}

/**
 * this is an optimized brute force solution while there are alot of nested loops the actual iteration counts will be relatively low compared to checking the entire board all the time
 * @param pattern
 * pattern to check in the form of a 2d vector of bools
 * @param center
 * cell to check for pattern from
 * @param clear
 * should the function clear the pattern if it is found
 * @return 
 */
std::pair<bool,std::vector<IntVector2>> GRID::GridSystem::MatchPatternsAroundNewCell(const std::vector<std::vector<int>>& pattern, IntVector2 center,bool clear)
{
    auto rotations = GenerateAllRotations(pattern);

    std::vector<IntVector2> patternCells;

    for (const auto& rotatedPattern : rotations)
    {

        int patternHeight = (int)rotatedPattern.size();
        int patternWidth = (int)rotatedPattern[0].size();

        int halfPatternHeight = patternHeight / 2;
        int halfPatternWidth = patternWidth / 2;

        //----------------------------------------------------------------
        //this section is to check the section of the grid the new cell can possibly create,
        //for example if we have a pattern that is just 4 continuous blocks, when you add a new block there will never be a situation where it creates a new pattern
        //more than 3 ((4/2)+1) cells to its left,right, above or below.
        for (int x = -halfPatternWidth -1 ; x <= halfPatternWidth + 1; ++x)  
        {
            for (int y = -halfPatternHeight - 1; y <= halfPatternHeight + 1; ++y)
            {
                bool match = true;
                patternCells.clear();
                //------------------------------------------------------------
                //this section checks the cells of the actual pattern
                for (int row = 0; row < patternHeight; ++row)
                {
                    for (int col = 0; col < patternWidth; ++col)
                    {
                        IntVector2 gridPos(center.x + x + col, center.y + y + row); 

                        
                        if (!GetCell(gridPos) || static_cast<bool>(rotatedPattern[row][col]) != GetCell(gridPos)->m_isObstacle)
                        {
                            match = false;
                            break;
                        }
                        patternCells.push_back(gridPos);
                    }
                    if (!match) break;
                }
                //-----------------------------------------------------------------
                if (match)
                {
                    if (clear)
                    {
                        ClearCells(patternCells);
                    }
                   // NotifyObservers(Events::EventType::Pattern);
                    return std::make_pair(true, patternCells);
                }
            }
        }
    }
    return std::make_pair(false,patternCells);
}


//simple way to check for all rotations, thank god no diagonals
std::vector<std::vector<std::vector<int>>> GRID::GridSystem::GenerateAllRotations(const std::vector<std::vector<int>>& pattern)
{
    std::vector<std::vector<std::vector<int>>> rotations;
    rotations.push_back(pattern);

    auto rotated90 = Rotate90(pattern);
    rotations.push_back(rotated90);

    auto rotated180 = Rotate90(rotated90);
    rotations.push_back(rotated180);

    auto rotated270 = Rotate90(rotated180);
    rotations.push_back(rotated270);

    return rotations;
}

void GRID::GridSystem::UpdateRowHash(int row)
{
    uint64_t hash = 0;
    for (int col = 0; col < m_gridSize.x; ++col)
    {
        hash = (hash << 1) | (m_grid[row][col].m_isObstacle ? 1 : 0);
    }
    m_rowHash_[row] = hash;
}

std::vector<std::vector<int>> GRID::GridSystem::Rotate90(const std::vector<std::vector<int>>& pattern)
{
    int rows = static_cast<int>(pattern.size());
    int cols = static_cast<int>(pattern[0].size());
    std::vector<std::vector<int>> rotated(cols, std::vector<int>(rows));

    for (int r = 0; r < rows; ++r)
    {
        for (int c = 0; c < cols; ++c)
        {
            rotated[c][rows - 1 - r] = pattern[r][c];
        }
    }
    return rotated;
}

void GRID::GridSystem::CreateGrid()
{
    m_grid.resize(m_gridSize.y, std::vector<Cell>(m_gridSize.x));

    for (int x = 0; x < m_gridSize.x; ++x)
    {
        for (int y = 0; y < m_gridSize.y; ++y)
        {
            m_grid[x][y] = Cell(IntVector2(x, y), false);
            m_grid[x][y].m_worldPosition = GridToWorld(IntVector2(x, y));
        }
    }
    m_rowHash_.resize(m_gridSize.y);
    for (int row = 0; row < m_gridSize.y; ++row)
    {
        UpdateRowHash(row);
    }
}

void GRID::GridSystem::ClearCells(std::vector<IntVector2> cells)
{
    for (auto cell : cells)
    {
        RemoveObstacle(cell);
    }
}
