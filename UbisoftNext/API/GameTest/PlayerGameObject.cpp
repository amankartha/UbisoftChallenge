#include "stdafx.h"
#include "PlayerGameObject.h"

#include "Game.h"
#include "GameObjectManager.h"
#include "GolfBallGameObject.h"


PlayerGameObject::PlayerGameObject(Game* instance, int id) : GameObject(instance,id)
{

}

void PlayerGameObject::Init()
{
	GameObject::Init();
	GameInstance->GetGameObjectManager()->AddToLookupTable("GolfBall", 
		GameInstance->GetGameObjectManager()->Create<GolfBallGameObject>("GolfBall", this));
}

void PlayerGameObject::Update(float DeltaTime)
{
	GameObject::Update(DeltaTime);
}

int PlayerGameObject::GetGolfBallID()
{
	return m_golf_ball_id;
}
