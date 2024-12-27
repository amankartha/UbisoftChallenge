#pragma once
#include <vector>
#include <map>
#include <CustomMath.h>

class CRenderer;

class Renderer
{
	static enum RenderLayer
	{
		Background = 0,
		Default = 1,
		UI = 3
	};

	  Vector2 shakeValue;
	  bool isShake;

	  std::map<RenderLayer, std::vector<CRenderer*>> RENDERMAP;
	
	 void RenderAll();

	 void AddRendererComponent(CRenderer& renderer);

	 void RemoveRendererComponent(CRenderer& renderer);

	 void SetShake(bool b);

	 void SetShakeOff();
	
};

