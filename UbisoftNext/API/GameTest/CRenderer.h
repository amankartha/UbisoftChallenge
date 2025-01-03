#pragma once
#include "Component.h"
#include "Renderer.h"
#include "appUtility.h"

class CRenderer :
    public Component
{


private:

    Renderer& mainRenderer;
    CSimpleSprite* sprite;
    RenderLayer m_renderLayer;
    bool m_isShake;

public:
    CRenderer(Renderer& renderer) : mainRenderer(renderer)
    {
        m_isShake = false;
        sprite = nullptr;
        m_renderLayer = RenderLayer::Default;
        mainRenderer.AddRendererComponent(*this);
    }
    ~CRenderer() override
    {
        mainRenderer.RemoveRendererComponent(*this);
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
        mainRenderer.RemoveRendererComponent(*this);
        m_renderLayer = layer;
        mainRenderer.AddRendererComponent(*this);
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

    void Render() override;

    void Render(Vector2& offset);
    
    void RenderWithCamera(Vector2 offset,float a,float zoom);

};

