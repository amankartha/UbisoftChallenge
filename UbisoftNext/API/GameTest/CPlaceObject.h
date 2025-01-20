#pragma once
#include "Component.h"
#include "Grid.h"
#include "InputHandler.h"

class CGameManager;

class CPlaceObject :
    public Component, public Events::IObserver
{
public:

	CPlaceObject(GameObject* gameObject, InputHandler* handler,GRID::GridSystem* grid_system);
	~CPlaceObject();
	void Init() override;
	void Update(float DeltaTime) override;

	CGameManager* GetGameManager();

	void OnNotify(Events::EventType event) override;
private:
	InputHandler* m_handler_;
	GRID::GridSystem* m_grid_system_;
	CGameManager* m_game_manager_;
};

