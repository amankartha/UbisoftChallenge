#pragma once
#include "Component.h"
#include "ObserverPattern.h"

class CBoostPad :
    public Component,Events::IPhysicsObserver
{
public:
	CBoostPad(GameObject* attachedObject);
	~CBoostPad();
	void Init() override;
	void Update(float DeltaTime) override;
	void Render() override;
	void OnTriggerEnter(int idOne, int idTwo) override;
	void OnCollisionEnter(int idOne, int idTwo) override;

private:
	std::vector<size_t> m_rigibody_ids;
	//bool m_mark_for_deletion = false;
};

