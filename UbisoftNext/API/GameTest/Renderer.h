#pragma once
#include <vector>
#include <map>
#include <CustomMath.h>

#include "ObjectPool.h"
#include "App/SimpleSprite.h"
#include "Camera.h"
#include "IRenderable.h"


class CRenderer;


namespace GRID
{
	class GridSystem;
};
enum RenderLayer
{
	Background = 0,
	Default = 1,
	UI = 2,
	end = 3
};
struct Renderable
{
public:

	Renderable() :m_sprite(".\\TestData\\tile_grey.png", 1, 1) {} ;


	~Renderable() = default;

	//
	//Renderable(const Renderable& other)
	//	: m_render_Function(other.m_render_Function),
	//	m_isOn(other.m_isOn),
	//	m_sprite(other.m_sprite) {
	//}

	//
	//Renderable& operator=(const Renderable& other) {
	//	if (this != &other) {
	//		m_render_Function = other.m_render_Function;
	//		m_isOn = other.m_isOn;
	//		m_sprite = other.m_sprite;
	//	}
	//	return *this;
	//}


	//Renderable(Renderable&& other) noexcept
	//	: m_render_Function(std::move(other.m_render_Function)),
	//	m_isOn(other.m_isOn),
	//	m_sprite(std::move(other.m_sprite)) {
	//	other.m_isOn = false;
	//}

	//
	//Renderable& operator=(Renderable&& other) noexcept {
	//	if (this != &other) {
	//		m_render_Function = std::move(other.m_render_Function);
	//		m_isOn = other.m_isOn;
	//		m_sprite = std::move(other.m_sprite);

	//		other.m_isOn = false;
	//	}
	//	return *this;
	//}
	
	 void Clear();
	 void Start();
	 RenderLayer GetRenderLayer() ;
	 void SetRenderLayer(RenderLayer layer) ;
	 void SetSprite(CSimpleSprite sprite)
	 {
		 m_sprite = sprite;
	 }

	// std::function<void(const Camera, bool)> m_render_Function;
	 bool m_isOn = false;
	 CSimpleSprite m_sprite;
	 IRenderable* m_renderable;
};

class Renderer
{
public:
	
	Renderer(Game* instance) 
	{
		for (int renderLayer = Background; renderLayer != end ; renderLayer++)
		{
			m_rendermap_[static_cast<RenderLayer>(renderLayer)] = std::make_unique<ObjectPool<Renderable>>(instance);
		}

		for (auto& layer : m_rendermap_)
		{
			layer.second.get()->InitializePool(100);
		}
		
		m_shakeValue = Vector2(0, 0);
		m_isShake = false;
	}
	~Renderer()
	{

	}

	Renderable* GetRenderable(RenderLayer layer, size_t id);

	void RenderAll(Camera& currentCamera);

	int AddRenderer(RenderLayer layer);

	void RemoveRenderer(RenderLayer layer,size_t id);

	void SetShake(bool b);

	void SetShakeOff();

	void DrawGridWithCamera(const Camera& camera,const GRID::GridSystem& gridSystem) const;
	 
public:
	Vector2 m_shakeValue;
	bool m_isShake;
private:
	std::map<RenderLayer,std::unique_ptr<ObjectPool<Renderable>>> m_rendermap_;

};

