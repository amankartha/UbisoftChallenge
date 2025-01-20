#include "stdafx.h"
#include "CGoal.h"

#include "CGameManager.h"
#include "Crigidbody.h"
#include "Game.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "Grid.h"
#include "PhysicsSimulation.h"


CGoal::CGoal(GameObject* attachedObject, std::vector<IntVector2> ids) : Component(attachedObject), m_ids_to_clear(ids)
{
}

CGoal::~CGoal()
{
	GetAttachedGameObject()->GameInstance->GetPhysicsSimulation()->DeRegisterPhysicsObserver(*this);
	GetAttachedGameObject()->GameInstance->GetGridSystem()->ClearPlaceAble(m_ids_to_clear);
}

void CGoal::Init()
{
	Component::Init();
	GetAttachedGameObject()->GameInstance->GetPhysicsSimulation()->RegisterPhysicsObserver(*this);
	m_rigibody_ids = GetAttachedGameObject()->GameInstance->GetGameObjectManager()->FindUsingTable("GameManager")
		->GetComponent<CGameManager>()->GetAllGolfBallRigidBodies();
}

void CGoal::Update(float DeltaTime)
{
	Component::Update(DeltaTime);
}

void CGoal::Render()
{
	Component::Render();
}

void CGoal::OnTriggerEnter(int idOne, int idTwo)
{
	size_t ownRbID = GetAttachedGameObject()->GetComponent<Crigidbody>()->GetRigidBodyId();

	for (int i = 0; i < m_rigibody_ids.size(); ++i)
	{
		if ((idOne == m_rigibody_ids[i] || idTwo == m_rigibody_ids[i]) && (idOne == ownRbID || idTwo == ownRbID))
		{
			GetAttachedGameObject()->GameInstance->GetGameObjectManager()->FindUsingTable("GameManager")
				->GetComponent<CGameManager>()->AddScoreToCurrentPlayer();
			GetAttachedGameObject()->GameInstance->GetGameObjectManager()->Destroy(this->GetAttachedGameObject()->m_id);
		}
	}
}

void CGoal::OnCollisionEnter(int idOne, int idTwo)
{
}
