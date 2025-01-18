#include "stdafx.h"
#include "CCameraController.h"

#include "Ccamera.h"
#include "Game.h"
#include "GameObject.h"
#include "InputHandler.h"

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

}

void CCameraController::OnNotify(const Events::EventType event)
{
	if (event == Events::EventType::Input)
	{
		InputHandler* inputHandler = GetAttachedGameObject()->GameInstance->GetInputHandler();
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

		GetAttachedGameObject()->GetTransformComponent().OffsetPosition(m_direction);
		m_direction = Vector2(0, 0);
	}
}


