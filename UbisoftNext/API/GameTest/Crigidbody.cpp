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

void Crigidbody::ClearBody()
{
	m_simulation_->RemoveBody(m_rigidbody_id);
	m_rigidbody_id = -1;
}

void Crigidbody::AddBody()
{
	if (m_rigidbody_id == -1)
	{
		if (radius_ == -1)
		{
		m_rigidbody_id = m_simulation_->AddBody(physics::Shape::BOX, is_static_, width_, height_, density_, physics::Material(density_, bounciness_), &GetAttachedGameObject()->GetTransformComponent(), is_trigger_);
		}
		else
		{
			m_rigidbody_id = m_simulation_->AddBody(physics::Shape::BOX, is_static_, radius_, density_, physics::Material(density_, bounciness_), &GetAttachedGameObject()->GetTransformComponent(), is_trigger_);
		}
	}
}

