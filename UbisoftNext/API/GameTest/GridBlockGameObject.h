#pragma once
#include "GameObject.h"

class CRenderer;
class Crigidbody;

class GridBlockGameObject :
    public GameObject
{
public:

	GridBlockGameObject(Game* instance);
	void Init() override;
	void Update(float DeltaTime) override;
	void Render() override;

	void Clear();
	void Start();
private:
	Crigidbody* m_crigidbody_;
	Ctransform* m_ctransform_;
	CRenderer* m_crenderer_;
};

