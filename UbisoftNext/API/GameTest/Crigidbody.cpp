#include "stdafx.h"
#include "Crigidbody.h"

Crigidbody::~Crigidbody()
{
	m_simulation_->RemoveBody(m_rigidbody_id);
}
