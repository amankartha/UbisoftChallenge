#pragma once
#include <vector>
#include <map>
#include <CustomMath.h>


class CRenderer;
class Camera;

namespace GRID
{
	class GridSystem;
};
enum RenderLayer
{
	Background = 0,
	Default = 1,
	UI = 3
};

class Renderer
{
public:
	
	Renderer()
	{
		RENDERMAP[RenderLayer::Default].reserve(1000);
	}
	~Renderer()
	{

	}
	
	void RenderAll(Transform CurrentCameraTransform,float zoom);

	void AddRendererComponent(CRenderer& renderer);

	void RemoveRendererComponent(CRenderer& renderer);

	void SetShake(bool b);

	void SetShakeOff();

	void DrawGridWithCamera(const Camera& camera,const GRID::GridSystem& gridSystem) const;
	 
public:
	Vector2 shakeValue;
	bool isShake;
private:
	std::map<RenderLayer, std::vector<CRenderer*>> RENDERMAP;
};

