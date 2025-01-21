#include "stdafx.h"
#include "CChangeSize.h"

#include "CGameManager.h"
#include "Crigidbody.h"
#include "Game.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "Grid.h"
#include "PhysicsSimulation.h"
#include "Scheduler.h"

CChangeSize::CChangeSize(GameObject* attachedObject, std::vector<IntVector2> ids) : Component(attachedObject), m_ids_to_clear(ids)
{
}

CChangeSize::~CChangeSize()
{
	GetAttachedGameObject()->GameInstance->GetPhysicsSimulation()->DeRegisterPhysicsObserver(*this);
	GetAttachedGameObject()->GameInstance->GetGridSystem()->ClearPlaceAble(m_ids_to_clear);
}

void CChangeSize::Init()
{
	Component::Init();
	GetAttachedGameObject()->GameInstance->GetPhysicsSimulation()->RegisterPhysicsObserver(*this);
	m_rigibody_ids = GetAttachedGameObject()->GameInstance->GetGameObjectManager()->FindUsingTable("GameManager")
		->GetComponent<CGameManager>()->GetAllGolfBallRigidBodies();
}

void CChangeSize::Update(float DeltaTime)
{
	Component::Update(DeltaTime);
}

void CChangeSize::Render()
{
	Component::Render();
}

void CChangeSize::OnTriggerEnter(int idOne, int idTwo)
{
	size_t ownRbID = GetAttachedGameObject()->GetComponent<Crigidbody>()->GetRigidBodyId();

	for (int i = 0; i < m_rigibody_ids.size(); ++i)
	{
		if ((idOne == m_rigibody_ids[i] || idTwo == m_rigibody_ids[i]) && (idOne == ownRbID || idTwo == ownRbID))
		{
			physics::RigidBody* rb = GetAttachedGameObject()->GameInstance->GetPhysicsSimulation()->GetBody(m_rigibody_ids[i]);
			std::pair<float,float> values = rb->GetCollider()->GetValues();

			float initialScale = rb->GetTransform()->GetScale();
			rb->SetScale(1.3f);
			rb->IncreaseSize(3.0f);
			GetAttachedGameObject()->GameInstance->GetScheduler()->AddTask(
				[rb,values,initialScale]()
				{
					rb->SetScale(initialScale);
					rb->SetValues(values);
				}, 5000

			);


			GetAttachedGameObject()->GameInstance->GetGameObjectManager()->Destroy(this->GetAttachedGameObject()->m_id);
			//GetAttachedGameObject()->GameInstance->GetPhysicsSimulation()->DeRegisterPhysicsObserver(*this);
			//m_mark_for_deletion = true;

		}
	}
}

void CChangeSize::OnCollisionEnter(int idOne, int idTwo)
{
}
