#include "stdafx.h"
#include "BulletGameObject.h"
#include "CRenderer.h"
#include "Game.h"



BulletGameObject::BulletGameObject(Game* instance) : GameObject(instance)
{
	m_transform = AddComponent<Ctransform>();
	AddComponent<CRenderer>(instance->GetRenderer())->CreateSprite(".\\TestData\\bulletRed.png", 1, 1);
	GetComponent<CRenderer>()->m_isOn = false;
	//GetComponent<CRenderer>()->SetRenderLayer(RenderLayer::Default);
//	GetComponent<CRenderer>()->SetGameObject(this);
	m_direction = Vector2(FRAND_RANGE(-1, 1), FRAND_RANGE(-1, 1));
	m_isActive = false;
}

void BulletGameObject::Init()
{ 
	GameObject::Init();
}

void BulletGameObject::Update()
{
	if (m_isActive)
	{
		//GameObject::Update();
		m_transform->OffsetPosition(m_direction);
	}
}



void BulletGameObject::Clear()
{
	m_transform->ResetLocalPosition();
	GetComponent<CRenderer>()->m_isOn = false;
	m_isActive = false;
}

void BulletGameObject::Start()
{
	m_isActive = true;
	GetComponent<CRenderer>()->m_isOn = true;
	return;
}
