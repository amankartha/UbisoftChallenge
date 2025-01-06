#pragma once

#include "App/app.h"
#include "CustomMath.h"

class Camera;

namespace App
{

	Vector2 GetMousePosVec2();
	
	Vector2 WorldToScreen(Camera& camera, Vector2 worldPos);

	Vector2 ScreenToWorld(Camera& camera, Vector2 screenPos);

};


