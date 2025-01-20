#include "stdafx.h"
#include "CGolfBall.h"

#include "cameraManager.h"
#include "CGameManager.h"
#include "CMiniGolfPlayer.h"
#include "Crigidbody.h"
#include "Game.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "InputHandler.h"

CGolfBall::CGolfBall(GameObject* attachedObject, int OwnerIndex, int ownerID) : Component(attachedObject), m_owner_index_(OwnerIndex),
m_state(nullptr),
m_crigidbody_(nullptr),
m_owner_id(ownerID)
{
	int m_owner_id;
	this->GetAttachedGameObject()->GameInstance->GetInputHandler()->RegisterObserver(*this);
}

CGolfBall::~CGolfBall()
{
	this->GetAttachedGameObject()->GameInstance->GetInputHandler()->DeRegisterObserver(*this);
}

void CGolfBall::Init()
{
	Component::Init();
}

void CGolfBall::Update(float DeltaTime)
{
	Component::Update(DeltaTime);



	/*if (GetAttachedGameObject()->GameInstance->GetInputHandler()->IsKey('T'))
	{

		GetAttachedGameObject()->GetComponent<Crigidbody>()->AddForce(Vector2(0, 10000));
	}*/

	/*if (GetAttachedGameObject()->GameInstance->GetInputHandler()->IsKey('W'))
	{
		GetAttachedGameObject()->GetComponent<Crigidbody>()->AddForce(Vector2(0, 5000));
	}
	if (GetAttachedGameObject()->GameInstance->GetInputHandler()->IsKey('S'))
	{
		GetAttachedGameObject()->GetComponent<Crigidbody>()->AddForce(Vector2(0, -5000));
	}
	if (GetAttachedGameObject()->GameInstance->GetInputHandler()->IsKey('A'))
	{
		GetAttachedGameObject()->GetComponent<Crigidbody>()->AddForce(Vector2(-5000, 0));
	}
	if (GetAttachedGameObject()->GameInstance->GetInputHandler()->IsKey('D'))
	{
		GetAttachedGameObject()->GetComponent<Crigidbody>()->AddForce(Vector2(5000, 0));
	}
	App::Print(500, 500, GetAttachedGameObject()->GetComponent<Crigidbody>()->GetVelocity().Print().c_str());*/

}

//void CGolfBall::UpdateState(PlayerState state)
//{
//	m_state = state;
//}

void CGolfBall::OnNotify(Events::EventType event)
{
	if (event == Events::EventType::Input)
	{
		switch (*GetPlayerState()) {
		
		case PlayerState::idle:
			break;
		case PlayerState::playing:
			
			if (GetInputHandler()->IsKeyPressed(VK_LBUTTON))
			{
				Vector2 mousePosition = App::ScreenToWorld(GetAttachedGameObject()->GameInstance->GetCameraManager()->GetMainCamera(), App::GetMousePosVec2());
				Vector2 direction = this->GetAttachedGameObject()->GetTransformComponent().GetWorldPosition() - mousePosition;
				GetRigidBody()->AddForce(direction * 10000);
				NotifyObservers(Events::EventType::BallHit);
			}
			break;
		}
	}
}

Crigidbody* CGolfBall::GetRigidBody()
{
	if (m_crigidbody_ == nullptr)
	{
		m_crigidbody_ = this->GetAttachedGameObject()->GetComponent<Crigidbody>();
	}
	return m_crigidbody_;
}

InputHandler* CGolfBall::GetInputHandler()
{
	{
		m_handler_ = GetAttachedGameObject()->GameInstance->GetInputHandler();
	}
	return m_handler_;
}

PlayerState* CGolfBall::GetPlayerState()
{
	if (m_state == nullptr)
	{
		m_state = &GetAttachedGameObject()->GameInstance->GetGameObjectManager()->Find(m_owner_id)->GetComponent<CMiniGolfPlayer>()->m_state_;
	}
	return m_state;
}

void CGolfBall::RegisterGameManagerObserver(CGameManager* observer)
{
	RegisterObserver(*observer);
}

void CGolfBall::RemoveGameManagerObserver(CGameManager* observer)
{
	DeRegisterObserver(*observer);
}


