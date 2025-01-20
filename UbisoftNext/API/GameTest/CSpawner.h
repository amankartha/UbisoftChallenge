#pragma once
#include "Component.h"
#include "CPoolManager.h"
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
};

