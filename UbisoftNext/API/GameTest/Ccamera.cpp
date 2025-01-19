#include "stdafx.h"
#include "Ccamera.h"
#include "appUtility.h"
#include "GameObject.h"
void Ccamera::Init()
{
	Component::Init();
}

void Ccamera::Update(float DeltaTime)
{
	Component::Update(DeltaTime);
	//m_camera->SetPosition(GetAttachedGameObject()->GetTransformComponent().GetWorldPosition());
}
