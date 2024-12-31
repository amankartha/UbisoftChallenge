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
	if (App::IsKeyPressed(VK_UP))
	{
		getAttachedGameObject()->GetTransform()->OffsetPosition(Vector2(0, 1));
	}
	if (App::IsKeyPressed(VK_DOWN))
	{
		getAttachedGameObject()->GetTransform()->OffsetPosition(Vector2(0, -1));
	}
	if (App::IsKeyPressed('M'))
	{
		getAttachedGameObject()->GetTransform()->OffsetRotation(1.0);
	}
	if (App::IsKeyPressed('Z'))
	{
		m_camera->SetZoom(m_camera->GetZoom() + 0.05);
	}
	if (App::IsKeyPressed('X'))
	{
		m_camera->SetZoom(m_camera->GetZoom() - 0.05);
	}

	//m_camera->SetPosition(getAttachedGameObject()->GetTransform()->GetPosition());
	m_camera->SetTransform(getAttachedGameObject()->GetTransformCopy());
}
