#include "stdafx.h"
#include "CPlaceObject.h"

#include "BulletGameObject.h"
#include "Game.h"
#include "GameObjectManager.h"

CPlaceObject::CPlaceObject(InputHandler* handler,GRID::GridSystem* grid_system) : m_handler_(handler), m_grid_system_(grid_system) 
{

}

CPlaceObject::~CPlaceObject()
{
	m_handler_->DeRegisterObserver(*this);
}

void CPlaceObject::Init()
{
	Component::Init();
	m_handler_->RegisterObserver(*this);
}

void CPlaceObject::Update()
{
	Component::Update();
}

void CPlaceObject::OnNotify(Events::EventType event)
{
	if (event == Events::EventType::Input)
	{
		if (m_handler_->IsKeyPressed(VK_RIGHT))
		{
		//	GetAttachedGameObject()->GameInstance->GetGameObjectManager()->Create<>();
		}
	}
}

