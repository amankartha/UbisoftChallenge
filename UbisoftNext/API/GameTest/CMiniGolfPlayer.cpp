#include "stdafx.h"
#include "CMiniGolfPlayer.h"

#include "CGolfBall.h"
#include "Game.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "CGameManager.h"
CMiniGolfPlayer::CMiniGolfPlayer(GameObject* attachedObject, int id, CGameManager* gm)
	: Component(attachedObject), m_state_(PlayerState::idle), m_golf_ball_id(id), m_game_manager_(gm)
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
	if (m_game_manager_)
	{
		m_game_manager_ = GetAttachedGameObject()->GameInstance->GetGameObjectManager()->FindUsingTable("GameManager")->GetComponent<CGameManager>();
	}
	return m_game_manager_;
}

CGolfBall* CMiniGolfPlayer::GetGolfBall()
{
	if (m_golf_ball_ == nullptr)
	{
		m_golf_ball_ = GetAttachedGameObject()->GameInstance->GetGameObjectManager()->Find(m_golf_ball_id)->GetComponent<CGolfBall>();
	}
	return m_golf_ball_;
}

void CMiniGolfPlayer::SetState(PlayerState state)
{
	m_state_ = state;
	//GetGolfBall()->UpdateState(state);
}
