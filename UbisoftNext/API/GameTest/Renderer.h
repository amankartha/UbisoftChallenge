#pragma once
#include <vector>
#include <map>

class CRenderer;
//Should this be a singleton?
enum RenderLayer
{
	Background = 0,
	Default = 1,
	UI = 3
};
class Renderer
{
public:
	static std::map<RenderLayer, std::vector<CRenderer*>> RENDERMAP;
	
	static void RenderAll();

	static void AddRendererComponent(CRenderer& renderer);

	static void RemoveRendererComponent(CRenderer& renderer);

	
};

