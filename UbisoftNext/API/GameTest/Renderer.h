#pragma once
#include <vector>
#include <map>
#include <CustomMath.h>

class CRenderer;
//Should this be a singleton?

namespace Renderer
{
	static enum RenderLayer
	{
		Background = 0,
		Default = 1,
		UI = 3
	};

	 static Vector2 shakeValue;
	 static bool isShake;

	 static std::map<RenderLayer, std::vector<CRenderer*>> RENDERMAP;
	
	 void RenderAll();

	 void AddRendererComponent(CRenderer& renderer);

	 void RemoveRendererComponent(CRenderer& renderer);

	 void SetShake(bool b);

	 void TurnOffShake();
	
};

