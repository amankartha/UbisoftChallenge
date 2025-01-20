#include "stdafx.h"
#include "CSpawner.h"

#include "BoostPadGameObject.h"
#include "Game.h"
#include "GameObject.h"
#include "GameObjectManager.h"
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

	std::pair<int,GridBlockGameObject*> block = m_gridBlock_pool_->SpawnAndReturnId();
	block.second->GetTransformComponent().SetPosition(GetGridSystem()->GridToWorld(gridPosition));
	m_initialized_pool_objects_[gridPosition] = block.first;

	std::pair<bool, std::vector<IntVector2>> results = 
		GetGridSystem()->MatchPatternsAroundNewCell({{ 1,1,1 }, { 0,0,0 }, { 1,1,1 }}, gridPosition, true);
	if (results.first )
	{
		int id = GetGame()->GetGameObjectManager()->Create<BoostPadGameObject>("BoostPad",results.second);
		GetGame()->GetGameObjectManager()->Find(id)->GetComponent<Ctransform>()
		->SetPosition(GetGridSystem()->GridToWorld(CalculateCenter(results.second)));
	}

	for (IntVector2 location : results.second )
	{
		auto it = m_initialized_pool_objects_.find(location);
		if (it!=m_initialized_pool_objects_.end())
		{
			m_gridBlock_pool_->Release(it->second);
			m_initialized_pool_objects_.erase(it);
		}
	}

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
