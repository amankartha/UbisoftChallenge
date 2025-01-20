#include "stdafx.h"
#include "CSpawner.h"

#include "BoostPadGameObject.h"
#include "ExtraBallGameObject.h"
#include "Game.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "GoalGameObject.h"
#include "Grid.h"

CSpawner::~CSpawner()
{
	GetGridSystem()->DeRegisterObserver(*this);
}

void CSpawner::Init()
{
	Component::Init();
	GetGridSystem()->RegisterObserver(*this);
}

void CSpawner::Update(float DeltaTime)
{
	Component::Update(DeltaTime);
}

void CSpawner::Render()
{
	Component::Render();
}

GRID::GridSystem* CSpawner::GetGridSystem()
{
	if (m_grid_system_ == nullptr)
	{
		m_grid_system_ = GetAttachedGameObject()->GameInstance->GetGridSystem();
	}
	return m_grid_system_;
}

Game* CSpawner::GetGame()
{
	if (m_game_ == nullptr)
	{
		m_game_ = GetAttachedGameObject()->GameInstance;
	}
	return m_game_;
}


void CSpawner::OnNotify(Events::PatternEventType event, IntVector2 gridPosition)
{
	//place block on grid
	std::pair<int,GridBlockGameObject*> block = m_gridBlock_pool_->SpawnAndReturnId();
	block.second->GetTransformComponent().SetPosition(GetGridSystem()->GridToWorld(gridPosition));
	m_initialized_pool_objects_[gridPosition] = block.first;


	//smallBalls
	FindMatch<ExtraBallGameObject>(gridPosition, { {1,1},{1,1} }, "ExtraBall");
	//match patterns
	//Boost Pad
	FindMatch<BoostPadGameObject>(gridPosition, { { 1,1,1 }, { 0,0,0 }, { 1,1,1 } },"boostPad");

	FindMatch<GoalGameObject>(gridPosition, { { 1,1,1 }, { 1,0,1 }, { 1,1,1 } },"Goal");




}

IntVector2 CSpawner::CalculateCenter(std::vector<IntVector2> points)
{
	int sumX = 0;
	int sumY = 0;

	for (auto point : points)
	{
		sumX += point.x;
		sumY += point.y;
	}

	int centerX = static_cast<int>(sumX / points.size());
	int centerY = static_cast<int>(sumY / points.size());

	return IntVector2(centerX, centerY);
}
