#pragma once
#include "BulletGameObject.h"
#include "Component.h"
#include "ObjectPool.h"

class CPoolManager :
    public Component
{
public:
    CPoolManager(Game* instance) : Component() , m_bullet_pool_(instance)
    {
	    
    }

    void Init() override;
    void Update() override;

    BulletGameObject* Spawn();
private:
    ObjectPool<BulletGameObject> m_bullet_pool_;
};

