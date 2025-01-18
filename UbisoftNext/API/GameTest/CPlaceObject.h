#pragma once
#include "Component.h"
#include "Grid.h"
#include "InputHandler.h"

class CPlaceObject :
    public Component,Events::IObserver
{
public:

	CPlaceObject(InputHandler* handler,GRID::GridSystem* grid_system);
	~CPlaceObject();
	void Init() override;
	void Update() override;

	void OnNotify(Events::EventType event) override;
private:
	InputHandler* m_handler_;
	GRID::GridSystem* m_grid_system_;
};

