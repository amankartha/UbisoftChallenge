#include "stdafx.h"
#include "CPlaceObject.h"

#include "BulletGameObject.h"
#include "cameraManager.h"
#include "CGameManager.h"
#include "Game.h"
#include "GameObjectManager.h"

CPlaceObject::CPlaceObject(GameObject* gameObject, InputHandler* handler,GRID::GridSystem* grid_system) :Component(gameObject),  m_handler_(handler), m_grid_system_(grid_system) 
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

void CPlaceObject::Update(float DeltaTime)
{
	Component::Update(DeltaTime);
}

CGameManager* CPlaceObject::GetGameManager()
{
	if (m_game_manager_ == nullptr)
	{
		m_game_manager_ = GetAttachedGameObject()->GameInstance->GetGameObjectManager()->FindUsingTable("GameManager")->GetComponent<CGameManager>();
	}
	return m_game_manager_;
}

void CPlaceObject::OnNotify(Events::EventType event) //Todo: Cleanup
{
	if (event == Events::EventType::Input)
	{
		if (m_handler_->IsKeyPressed(VK_RBUTTON)
			&& GetAttachedGameObject()->GameInstance->GetGridSystem()
			->GetCellFromWorldPosition(App::ScreenToWorld(m_attachedGameObject->GameInstance->GetCameraManager()->GetMainCamera(), m_attachedGameObject->GetTransformComponent().GetWorldPosition()))
			->m_isPlaceable
			&& GetGameManager()->RemoveATBFromPlayer(GetGameManager()->m_current_player,1))
		{
			m_grid_system_->SetObstacle(App::ScreenToWorld(m_attachedGameObject->GameInstance->GetCameraManager()->GetMainCamera(),  m_attachedGameObject->GetTransformComponent().GetWorldPosition()));
		}
	}
}

