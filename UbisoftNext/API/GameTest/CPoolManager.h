#pragma once
#include "BulletGameObject.h"
#include "Component.h"
#include "ObjectPool.h"

class Scheduler;

class CPoolManager :
    public Component
{
public:
    CPoolManager(Game* instance) :  m_bullet_pool_(instance)
    {
        m_game_ = instance;
    }

    void Init() override;
    void Update() override;

    BulletGameObject* Spawn();

    int GetObjectPoolCount();
    int GetObjectPoolSize();
    int GetFlagSize();
private:
    ObjectPool<BulletGameObject> m_bullet_pool_;
    Game* m_game_;
};

