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

void App::PrintOutputMessage(std::string message)
{
	OutputDebugStringA(message.c_str());
}

void App::DrawCircle(const float cx, const float cy, const float r, const float segments, const float red,
	const float green, const float blue)
{
	float angleStep = 2.0f * PI / segments; 
	for (int i = 0; i < segments; ++i) {
		float t1 = (float)i * angleStep;              
		float t2 = ((float)i + 1.0) * angleStep;        

	
		float x1 = cx + r * cos(t1);
		float y1 = cy + r * sin(t1);
		float x2 = cx + r * cos(t2);
		float y2 = cy + r * sin(t2);

		
		DrawLine(x1, y1, x2, y2, red, green, blue);
	}
}

void App::DrawBox(const float cx, const float cy, const float width, const float height,
	const float red, const float green, const float blue)
{
	float LeftX = cx - width / 2 ;
	float RightX = cx + width / 2 ;
	float topY = cy + height / 2;
	float bottomY = cy - height / 2;


	DrawLine(LeftX, bottomY, RightX, bottomY, red, green, blue);
	DrawLine(LeftX, topY, RightX, topY, red, green, blue);
	DrawLine(LeftX, bottomY, LeftX, topY, red, green, blue);
	DrawLine(RightX, bottomY, RightX, topY, red, green, blue);
}


