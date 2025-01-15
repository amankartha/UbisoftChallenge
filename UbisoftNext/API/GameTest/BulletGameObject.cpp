#include "stdafx.h"
#include "BulletGameObject.h"
#include "CRenderer.h"
#include "Game.h"

BulletGameObject::BulletGameObject(Game* instance, ObjectPool<BulletGameObject>* pool) : GameObject(instance)
{
	AddComponent<Ctransform>();
	AddComponent<CRenderer>(instance->GetRenderer())->CreateSprite(".\\TestData\\bulletRed.png", 1, 1);
	GetComponent<CRenderer>()->SetRenderLayer(RenderLayer::Default);
	GetComponent<CRenderer>()->SetGameObject(this);
	m_pool_ = pool;
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
		GameObject::Update();
		GetTransformComponent().OffsetPosition(Vector2(1, 1));
	}
}



void BulletGameObject::Clear()
{
	GetTransformComponent().ResetLocalPosition();
	m_isActive = false;
}

void BulletGameObject::Start()
{
	m_isActive = true;
	return;
}
