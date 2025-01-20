#include "stdafx.h"
#include "Crigidbody.h"

Crigidbody::~Crigidbody()
{
	m_simulation_->RemoveBody(m_rigidbody_id);
}

void Crigidbody::AddForce(Vector2 force) const
{
	m_simulation_->GetBody(m_rigidbody_id)->AddForce(force);
}

Vector2 Crigidbody::GetVelocity()
{
	return m_simulation_->GetBody(m_rigidbody_id)->m_linearVelocity;
}

size_t Crigidbody::GetRigidBodyId()
{
	return m_rigidbody_id;
}

