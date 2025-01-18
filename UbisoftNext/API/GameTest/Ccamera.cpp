#include "stdafx.h"
#include "Ccamera.h"
#include "appUtility.h"
#include "GameObject.h"
void Ccamera::Init()
{
	Component::Init();
}

void Ccamera::Update()
{
	Component::Update();
	//m_camera->SetPosition(GetAttachedGameObject()->GetTransformComponent().GetWorldPosition());
}
