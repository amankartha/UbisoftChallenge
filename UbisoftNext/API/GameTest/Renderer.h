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

	Renderable() :m_sprite(".\\TestData\\tile_grey.png", 1, 1) {};   // Didnt want to touch Csprite so for no there is a default sprite


	~Renderable() = default;

	//
	//Renderable(const Renderable& other)                  //I dont need these but just incase ive commented them
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
	
	Renderer(Game* instance);

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

	static void DrawGridWithCameraAroundTransform(Ctransform* cameraTransform, const GRID::GridSystem& gridSystem, Ctransform* cursorTransform);

	void DrawFilledCells(const GRID::GridSystem& gridSystem);


	void RenderWithCamera(Vector2 offset, float a, float zoom, std::vector<Vector2> worldPositions);
	
	 
public:
	Vector2 m_shakeValue;
	bool m_isShake;
private:
	std::map<RenderLayer,std::unique_ptr<ObjectPool<Renderable>>> m_rendermap_;
	CSimpleSprite* m_gridFill_sprite;
	Game* m_game_instance;
};

