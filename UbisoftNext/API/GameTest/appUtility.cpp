#include "stdafx.h"
#include "appUtility.h"

Vector2 App::GetMousePosVec2()
{
	float x, y;
	GetMousePos(x, y);
	return Vector2(x , y);
}
