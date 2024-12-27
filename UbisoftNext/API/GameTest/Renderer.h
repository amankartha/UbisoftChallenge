#pragma once
#include <vector>
#include <map>
#include <CustomMath.h>

class CRenderer;

enum RenderLayer
{
	Background = 0,
	Default = 1,
	UI = 3
};

class Renderer
{
	std::map<RenderLayer, std::vector<CRenderer*>> RENDERMAP;
public:
	

	  Vector2 shakeValue;
	  bool isShake;

	  
	
	 void RenderAll();

	 void AddRendererComponent(CRenderer& renderer);

	 void RemoveRendererComponent(CRenderer& renderer);

	 void SetShake(bool b);

	 void SetShakeOff();
	
};

