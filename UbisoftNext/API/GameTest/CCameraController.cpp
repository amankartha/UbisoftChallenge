#include "stdafx.h"
#include "CCameraController.h"

#include "Ccamera.h"
#include "Game.h"
#include "GameObject.h"
#include "InputHandler.h"


CCameraController::CCameraController(GameObject* gameObject) : Component(gameObject), m_state_(CameraState::FollowGolfBall)
{
	m_direction = Vector2(0, 0);
}

CCameraController::~CCameraController()
{
	GetAttachedGameObject()->GameInstance->GetInputHandler()->DeRegisterObserver(*this);
}

void CCameraController::Init()
{
	Component::Init();
	GetAttachedGameObject()->GameInstance->GetInputHandler()->RegisterObserver(*this);

}

void CCameraController::Update()
{
	Component::Update();
	GetAttachedGameObject()->GetTransformComponent().OffsetPosition(m_direction);
	m_direction = Vector2(0, 0);

}

void CCameraController::OnNotify(const Events::EventType event)
{
	InputHandler* inputHandler = GetAttachedGameObject()->GameInstance->GetInputHandler();

	switch (m_state_) {
		case CameraState::FollowGolfBall:
			
			if (inputHandler->IsKeyPressed('F'))
			{
				m_state_ = CameraState::FreeRoam;
			}
			break;
		case CameraState::LerpToGolfBall:
			break;
		case CameraState::FreeRoam:
			if (event == Events::EventType::Input)
			{
				if (inputHandler->IsKey('W'))
				{
					m_direction += Vector2(0, 1);
				}
				if (inputHandler->IsKey('S'))
				{
					m_direction += Vector2(0, -1);
				}
				if (inputHandler->IsKey('A'))
				{
					m_direction += Vector2(-1, 0);
				}
				if (inputHandler->IsKey('D'))
				{
					m_direction += Vector2(1, 0);
				}
				if (inputHandler->IsKeyPressed('F'))
				{
					m_state_ = CameraState::FollowGolfBall;
					return;
				}
			}
			break;
	}


}
