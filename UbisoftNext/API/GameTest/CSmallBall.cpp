#include "stdafx.h"
#include "CSmallBall.h"

#include "Game.h"
#include "GameObject.h"
#include "Grid.h"

CSmallBall::CSmallBall(GameObject* attachedObject, std::vector<IntVector2> ids) : Component(attachedObject),m_ids_to_clear(ids)
{
}

CSmallBall::~CSmallBall()
{
	GetAttachedGameObject()->GameInstance->GetGridSystem()->ClearPlaceAble(m_ids_to_clear);
}

void CSmallBall::Init()
{
	Component::Init();
}

void CSmallBall::Update(float DeltaTime)
{
	Component::Update(DeltaTime);
}

void CSmallBall::Render()
{
	Component::Render();
}
