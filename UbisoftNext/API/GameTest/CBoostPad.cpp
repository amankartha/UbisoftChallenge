#include "stdafx.h"
#include "CBoostPad.h"

#include "CGameManager.h"
#include "Crigidbody.h"
#include "Game.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "PhysicsSimulation.h"

CBoostPad::CBoostPad(GameObject* attachedObject) : Component(attachedObject)
{
}

CBoostPad::~CBoostPad()
{
	GetAttachedGameObject()->GameInstance->GetPhysicsSimulation()->DeRegisterPhysicsObserver(*this);
}

void CBoostPad::Init()
{
	Component::Init();
	GetAttachedGameObject()->GameInstance->GetPhysicsSimulation()->RegisterPhysicsObserver(*this);
	m_rigibody_ids = GetAttachedGameObject()->GameInstance->GetGameObjectManager()->FindUsingTable("GameManager")
		->GetComponent<CGameManager>()->GetAllGolfBallRigidBodies();

}

void CBoostPad::Update(float DeltaTime)
{
	Component::Update(DeltaTime);
	//if (m_mark_for_deletion) GetAttachedGameObject()->GameInstance->GetGameObjectManager()->Destroy(this->GetAttachedGameObject()->m_id);
}

void CBoostPad::Render()
{
	Component::Render();
}

void CBoostPad::OnTriggerEnter(int idOne, int idTwo)
{
	size_t ownRbID = GetAttachedGameObject()->GetComponent<Crigidbody>()->GetRigidBodyId();

	for (int i = 0; i < m_rigibody_ids.size(); ++i)
	{
		if ((idOne == m_rigibody_ids[i] || idTwo == m_rigibody_ids[i]) && (idOne == ownRbID || idTwo == ownRbID))
		{
			physics::RigidBody* rb = GetAttachedGameObject()->GameInstance->GetPhysicsSimulation()->GetBody(m_rigibody_ids[i]);
			rb->AddForce(rb->GetVelocity() * 100000);
			GetAttachedGameObject()->GameInstance->GetGameObjectManager()->Destroy(this->GetAttachedGameObject()->m_id);
			//GetAttachedGameObject()->GameInstance->GetPhysicsSimulation()->DeRegisterPhysicsObserver(*this);
			//m_mark_for_deletion = true;
			
		}
	}
}

void CBoostPad::OnCollisionEnter(int idOne, int idTwo)
{
}
