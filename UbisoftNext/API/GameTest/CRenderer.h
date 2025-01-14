#pragma once
#include "Component.h"
#include "Renderer.h"
#include "appUtility.h"

class CRenderer :
    public Component, public IRenderable
{


private:

    Renderer* mainRenderer;
    CSimpleSprite* sprite;
    RenderLayer m_renderLayer;
    bool m_isShake;

public:
    CRenderer(Renderer* renderer) : mainRenderer(renderer)
    {
        m_isShake = false;
        sprite = nullptr;
        m_renderLayer = RenderLayer::Default;
        mainRenderer->AddRenderer(*this);
    }
    ~CRenderer() override
    {
        mainRenderer->RemoveRenderer(*this);
    }
    CSimpleSprite* GetSprite()
    {
        return sprite;
    }

    RenderLayer GetRenderLayer()
    {
        return m_renderLayer;
    }
    void SetRenderLayer(RenderLayer layer)
    {
        mainRenderer->RemoveRenderer(*this);
        m_renderLayer = layer;
        mainRenderer->AddRenderer(*this);
    }



    void CreateSprite(const char* fileName,int columns, int rows)
    {
        sprite = App::CreateSprite(fileName, columns, rows);
    } 

    void Shake(bool b)
    {
        m_isShake = b;
    }

    void Update() override;

    void Render(const Camera camera,bool isUI) override;

    
    void RenderWithCamera(Vector2 offset,float a,float zoom);

};

