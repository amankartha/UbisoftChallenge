#include "stdafx.h"
#include "PlayerGameObject.h"

#include "Game.h"
#include "GameObjectManager.h"
#include "GolfBallGameObject.h"


PlayerGameObject::PlayerGameObject(Game* instance, int id) : GameObject(instance,id)
{
	m_golf_ball_id = instance->GetGameObjectManager()->Create<GolfBallGameObject>("GolfBall", this);
}

void PlayerGameObject::Init()
{
	GameObject::Init();
}

void PlayerGameObject::Update(float DeltaTime)
{
	GameObject::Update(DeltaTime);
}

void PlayerGameObject::GetGolfBallID()
{
	return m_golf_ball_id;
}
