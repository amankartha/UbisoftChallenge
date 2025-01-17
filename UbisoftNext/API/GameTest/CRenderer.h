#pragma once
#include "Component.h"
#include "Renderer.h"
#include "appUtility.h"

class CRenderer :
    public Component,public IRenderable
{
public:
    CRenderer(Renderer* renderer,RenderLayer layer = RenderLayer::Default);
    CRenderer(Renderer* renderer,bool turnOnImmediately, RenderLayer layer = RenderLayer::Default);

    ~CRenderer() override;

    CSimpleSprite* GetSprite();

    void SetSprite(CSimpleSprite sprite);

    RenderLayer GetRenderLayer();

    void SetRenderLayer(RenderLayer layer);

    void SetRendererOnOff(bool state);


    void Shake(bool b);

    void Update() override;

    void Render(const Camera camera,bool isUI) override;

    
    void RenderWithCamera(Vector2 offset,float a,float zoom);

private:
    size_t m_id;
    Renderer* m_main_renderer_;
    RenderLayer m_renderLayer;
    bool m_isShake;

};

