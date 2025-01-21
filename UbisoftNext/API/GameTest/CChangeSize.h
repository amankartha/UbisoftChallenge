#pragma once
#include "Component.h"
#include "ObserverPattern.h"

class CChangeSize :
	public Component, Events::IPhysicsObserver
{
public:
	CChangeSize(GameObject* attachedObject, std::vector<IntVector2> ids);
	~CChangeSize();
	void Init() override;
	void Update(float DeltaTime) override;
	void Render() override;
	void OnTriggerEnter(int idOne, int idTwo) override;
	void OnCollisionEnter(int idOne, int idTwo) override;

private:
	std::vector<size_t> m_rigibody_ids;
	std::vector<IntVector2> m_ids_to_clear;
	//bool m_mark_for_deletion = false;
};
