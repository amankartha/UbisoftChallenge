#include "stdafx.h"
#include "Ccursor.h"
#include "GameObject.h"
#include "appUtility.h"
void Ccursor::Init()
{

	if (auto gameobject = getAttachedGameObject().lock())
	{
		m_transform = gameobject->GetComponent<Ctransform>();
	}
}

void Ccursor::Update()
{
	if (App::IsKeyPressed(WM_LBUTTONDOWN))
	{

	}
}
