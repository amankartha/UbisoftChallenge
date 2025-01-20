#include "stdafx.h"
#include "PlayerGameObject.h"

#include "CMiniGolfPlayer.h"
#include "Game.h"
#include "GameObjectManager.h"
#include "GolfBallGameObject.h"
#include "CGameManager.h"
#include "CGolfBall.h"

PlayerGameObject::PlayerGameObject(Game* instance, int id,int ownIndex) : GameObject(instance,id), m_ownIndex(ownIndex)
{

}

void PlayerGameObject::Init()
{
	GameObject::Init();
	int id = GameInstance->GetGameObjectManager()->Create<GolfBallGameObject>("GolfBall" + m_ownIndex,m_ownIndex);
	// + m_ownIndex,m_ownIndex);

	AddComponent<CMiniGolfPlayer>(id);
}

void PlayerGameObject::Update(float DeltaTime)
{
	GameObject::Update(DeltaTime);
}

int PlayerGameObject::GetGolfBallID()
{
	return m_golf_ball_id;
}
