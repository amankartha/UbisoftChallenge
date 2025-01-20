#include "stdafx.h"
#include "CMiniGolfPlayer.h"

CMiniGolfPlayer::CMiniGolfPlayer(GameObject* attachedObject, CGameManager* manager,CGolfBall* ball): Component(attachedObject) ,
m_game_manager_(manager),
m_golf_ball_(ball)
{

}

void CMiniGolfPlayer::Init()
{
	Component::Init();
}

void CMiniGolfPlayer::Update(float DeltaTime)
{
	Component::Update(DeltaTime);
}

void CMiniGolfPlayer::Render()
{
	Component::Render();
}

CGameManager* CMiniGolfPlayer::GetGameManager()
{
	return nullptr;
}

CGolfBall* CMiniGolfPlayer::GetGolfBall()
{
	return nullptr;
}
