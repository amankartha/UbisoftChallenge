#pragma once
#include "Component.h"
#include "CPoolManager.h"
#include "GameObjectManager.h"
#include "Grid.h"
#include "GridBlockGameObject.h"
#include "ObjectPool.h"
#include "ObserverPattern.h"

class Game;

namespace GRID
{
	class GridSystem;
}

class CSpawner :
    public Component , public Events::IPatternObserver
{
public:
	CSpawner(GameObject* attachedObject, CPoolManager<GridBlockGameObject>* go)
		: Component(attachedObject) ,m_gridBlock_pool_(go)
	{
	}
	~CSpawner();
	void Init() override;
	void Update(float DeltaTime) override;
	void Render() override;
	GRID::GridSystem* GetGridSystem();
	Game* GetGame();
	void OnNotify(Events::PatternEventType event, IntVector2 gridPosition) override;
private:
	IntVector2 CalculateCenter(std::vector<IntVector2> points);
private:
	GRID::GridSystem* m_grid_system_;
	Game* m_game_;
	CPoolManager<GridBlockGameObject>* m_gridBlock_pool_;
	std::unordered_map<IntVector2, int> m_initialized_pool_objects_;


	template<typename T>
	void FindMatch(IntVector2 gridPosition, std::vector<std::vector<int>> pattern, std::string name,int count = 1,bool setNotPLaceable =true)
	{
		std::pair<bool, std::vector<IntVector2>> results =
			GetGridSystem()->MatchPatternsAroundNewCell(pattern, gridPosition, true);

		if (results.first)
		{
			for (int i = 0; i < count; ++i)
			{
				int id = GetGame()->GetGameObjectManager()->Create<T>(name, results.second);

				GetGame()->GetGameObjectManager()->Find(id)->GetComponent<Ctransform>()
					->SetPosition(GetGridSystem()->GridToWorld(CalculateCenter(results.second)) 
						+ Vector2(FRAND_RANGE(-30,30),FRAND_RANGE(-30,30)));
			}
			//Set the cells to not be placeable on top of new pattern
			if (setNotPLaceable)
			{
				GetGridSystem()->SetCellsNotPlaceAble(results.second);
			}
			else
			{
				GetGridSystem()->ClearPlaceAble(results.second);
			}
			//clear blocks when pattern found
			for (IntVector2 location : results.second)
			{
				auto it = m_initialized_pool_objects_.find(location);
				if (it != m_initialized_pool_objects_.end())
				{
					m_gridBlock_pool_->Release(it->second);
					m_initialized_pool_objects_.erase(it);
				}
			}
		}
	}
};

