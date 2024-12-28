#include "stdafx.h"
#include "Ccamera.h"
#include "appUtility.h"
#include "GameObject.h"
void Ccamera::Init()
{
	
}

void Ccamera::Update()
{

	if (App::IsKeyPressed(VK_RIGHT))
	{
		getAttachedGameObject()->GetTransform()->OffsetPosition(Vector2(1,0));
	}
	if (App::IsKeyPressed(VK_LEFT))
	{
		getAttachedGameObject()->GetTransform()->OffsetPosition(Vector2(-1,0));
	}


	m_camera->SetPosition(getAttachedGameObject()->GetTransform()->GetPosition());
}
