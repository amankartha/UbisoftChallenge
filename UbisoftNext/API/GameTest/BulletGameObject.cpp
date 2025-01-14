#include "stdafx.h"
#include "BulletGameObject.h"
#include "CRenderer.h"
#include "Game.h"
//
//BulletGameObject::BulletGameObject(Game* instance, ObjectPool<BulletGameObject>& pool): GameObject(instance)
//{
//	AddComponent<CRenderer>(instance->GetRenderer())->CreateSprite(".\\TestData\\bulletRed.png", 1, 1);
//	GetComponent<CRenderer>()->SetRenderLayer(RenderLayer::Default);
//	m_pool_ = &pool;
//}
//
//void BulletGameObject::Init()
//{
//	GameObject::Init();
//}
//
//void BulletGameObject::Update()
//{
//	GameObject::Update();
//	GetTransformComponent().OffsetPosition(Vector2(1, 1));
//}
//
//
//
//void BulletGameObject::Clear()
//{
//	GetTransformComponent().ResetLocalPosition();
//}
//
//void BulletGameObject::Start()
//{
//	return;
//}
