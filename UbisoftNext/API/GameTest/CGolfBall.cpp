#include "stdafx.h"
#include "CGolfBall.h"

#include "Crigidbody.h"
#include "Game.h"
#include "GameObject.h"
#include "InputHandler.h"

void CGolfBall::Init()
{
	Component::Init();
}

void CGolfBall::Update(float DeltaTime)
{
	Component::Update(DeltaTime);

	if (GetAttachedGameObject()->GameInstance->GetInputHandler()->IsKeyPressed('T'))
	{

		GetAttachedGameObject()->GetComponent<Crigidbody>()->AddForce(Vector2(100, 150));
	}
}
