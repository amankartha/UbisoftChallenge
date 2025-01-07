#include "stdafx.h"
#include "appUtility.h"
#include "Camera.h"

Vector2 App::GetMousePosVec2()
{
	float x, y;
	GetMousePos(x, y);
	return Vector2(x , y);
}

Vector2 App::WorldToScreen(const Camera& camera, Vector2 worldPos)
{
	return (worldPos - camera.GetPosition()) 
			* camera.GetZoom()
		    + Vector2(APP_VIRTUAL_WIDTH/2,APP_VIRTUAL_HEIGHT/2);
}

Vector2 App::ScreenToWorld(const Camera& camera, Vector2 screenPos)
{
	return Vector2((screenPos - Vector2(APP_VIRTUAL_WIDTH/2,APP_VIRTUAL_HEIGHT/2)
					/ camera.GetZoom()) 
					+ camera.GetPosition());
}


