#pragma once
#include "GameObject.h"
#include "ObjectPool.h"


class BulletGameObject : public GameObject
{
public:
	BulletGameObject() {
		
	}

	BulletGameObject(Game* instance,ObjectPool<BulletGameObject>* pool);

	
	void Init() override;
	void Update() override;
	void Clear();
	void Start();
private:
	ObjectPool<BulletGameObject>* m_pool_;
	bool m_isActive = false;
	
};



