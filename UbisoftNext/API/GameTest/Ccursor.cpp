#include "stdafx.h"
#include "Ccursor.h"
#include "GameObject.h"
#include "appUtility.h"
void Ccursor::Init()
{

	
	m_transform = getAttachedGameObject()->GetComponent<Ctransform>();
	
}

void Ccursor::Update()
{
	
}
