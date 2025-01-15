#include "stdafx.h"
#include "CPoolManager.h"

void CPoolManager::Init()
{
	Component::Init();
}

void CPoolManager::Update()
{
	Component::Update();
	m_bullet_pool_.UpdateEachInUse();
}

BulletGameObject* CPoolManager::Spawn()
{
	return m_bullet_pool_.Get();
}
