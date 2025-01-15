#include "stdafx.h"
#include "CPoolManager.h"

#include "Game.h"
#include "Scheduler.h"

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
	PoolableObject<BulletGameObject>* g = m_bullet_pool_.Get();
	int id = g->m_index;
	m_game_->GetScheduler()->AddTask([this,id]() {m_bullet_pool_.Release(id); }, 1500);
	return &g->obj;
}

int CPoolManager::GetObjectPoolCount()
{
	return m_bullet_pool_.availableCount();
}

int CPoolManager::GetObjectPoolSize()
{
	return m_bullet_pool_.size();
}

int CPoolManager::GetFlagSize()
{
	return m_bullet_pool_.SizeOFFlags();
}
