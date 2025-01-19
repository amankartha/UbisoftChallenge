#pragma once
#include "GameObject.h"
#include "ObjectPool.h"


class BulletGameObject : public GameObject
{
public:

	BulletGameObject(Game* instance);

	
	void Init() override;
	void Update(float DeltaTime) override;
	void Clear();
	void Start();
private:
	ObjectPool<BulletGameObject>* m_pool_;
	bool m_isActive = false;
	Vector2 m_direction;
	Ctransform* m_transform;
};



