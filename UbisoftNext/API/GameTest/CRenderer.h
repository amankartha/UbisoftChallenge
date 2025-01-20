#pragma once
#include "Component.h"
#include "Renderer.h"
#include "appUtility.h"

class CRenderer :
    public Component,public IRenderable
{
public:
    CRenderer(GameObject* gameObject,  Renderer* renderer, RenderLayer layer = RenderLayer::Default);
    CRenderer(GameObject* gameObject, Renderer* renderer,bool turnOnImmediately , RenderLayer layer = RenderLayer::Default);

    ~CRenderer() override;

    CSimpleSprite* GetSprite();

    void SetSprite(CSimpleSprite sprite);

    RenderLayer GetRenderLayer();

    void SetRenderLayer(RenderLayer layer);

    void SetRendererOnOff(bool state);


    void Shake(bool b);

    void Update(float DeltaTime) override;

    void Render(const Camera camera,bool isUI) override;

    void SetTiled(IntVector2 tilingSize);
    
    void RenderWithCamera(Vector2 offset,float a,float zoom);

private:
    size_t m_id;
    Renderer* m_main_renderer_;
    RenderLayer m_renderLayer;
    bool m_isShake;
    bool m_isTiled;
    IntVector2 m_tiling;

};

