#include "stdafx.h"
#include "Crigidbody.h"

Crigidbody::~Crigidbody()
{
	m_simulation_->RemoveBody(m_rigidbody_id);
}

void Crigidbody::AddForce(Vector2 force)
{
	m_simulation_->GetBody(m_rigidbody_id)->AddForce(force);
}
