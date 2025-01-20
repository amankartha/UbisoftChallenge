#pragma once
#include "Component.h"
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
	CSpawner(GameObject* attachedObject)
		: Component(attachedObject)
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
};

