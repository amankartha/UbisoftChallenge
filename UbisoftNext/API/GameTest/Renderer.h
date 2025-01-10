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
class IRenderable
{
public:
	virtual ~IRenderable() {};
	virtual void Render(const Camera camera, bool isUI = false) = 0;
	virtual RenderLayer GetRenderLayer() = 0;
	virtual void SetRenderLayer(RenderLayer layer) = 0;
};

class Renderer
{
public:
	
	Renderer()
	{
		m_rendermap_[RenderLayer::Default].reserve(1000);
		m_shakeValue = Vector2(0, 0);
		m_isShake = false;
	}
	~Renderer()
	{

	}
	
	void RenderAll(Camera& currentCamera);

	void AddRenderer(IRenderable& renderer);

	void RemoveRenderer(IRenderable& renderer);

	void SetShake(bool b);

	void SetShakeOff();

	void DrawGridWithCamera(const Camera& camera,const GRID::GridSystem& gridSystem) const;
	 
public:
	Vector2 m_shakeValue;
	bool m_isShake;
private:
	std::map<RenderLayer, std::vector<IRenderable*>> m_rendermap_;
};

