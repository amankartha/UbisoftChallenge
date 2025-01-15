#pragma once

#include "App/app.h"
#include "CustomMath.h"

class Camera;

namespace App
{

	Vector2 GetMousePosVec2();
	
	Vector2 WorldToScreen(const Camera& camera, Vector2 worldPos);

	Vector2 ScreenToWorld(const Camera& camera, Vector2 screenPos);

	template<typename T>
	inline void RemoveFromVector(std::vector<T>& v, const T& item)
	{
		auto new_end = std::remove(v.begin(), v.end(), item);
		v.erase(new_end, v.end());
	}

	void PrintOutputMessage(std::string message);
};


