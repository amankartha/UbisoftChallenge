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
