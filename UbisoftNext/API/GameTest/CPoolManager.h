#pragma once

#include "Component.h"
#include "ObjectPool.h"
#include "Game.h"
class Scheduler;

template<typename T>
class CPoolManager :
    public Component
{
public:
    template<typename... Args>
    CPoolManager(Game* instance,size_t initialSize, Args&&... args) :  m_pool_(instance)
    {
        m_game_ = instance;
        m_pool_.InitializePool(initialSize,std::forward<Args>(args)...);
    }

    void Init() override;
    void Update() override;

    T* Spawn();

    int GetObjectPoolCount();
    size_t GetObjectPoolSize();
    size_t GetFlagSize();
private:
    ObjectPool<T> m_pool_;
    Game* m_game_;
};

template <typename T>
void CPoolManager<T>::Init()
{
	Component::Init();
}

template <typename T>
void CPoolManager<T>::Update()
{
    Component::Update();
    m_pool_.UpdateEachInUse();
}

template <typename T>
T* CPoolManager<T>::Spawn()
{
    PoolableObject<T>* g = m_pool_.Get(m_game_);
    size_t id = g->m_index;
    //m_game_->GetScheduler()->AddTask([this, id]() {m_pool_.Release(id); }, 5000);
    return &g->obj;
}


template <typename T>
int CPoolManager<T>::GetObjectPoolCount()
{
    return m_pool_.availableCount();
}

template <typename T>
size_t CPoolManager<T>::GetObjectPoolSize()
{
    return m_pool_.size();
}

template <typename T>
size_t CPoolManager<T>::GetFlagSize()
{
    return m_pool_.SizeOFFlags();
}
