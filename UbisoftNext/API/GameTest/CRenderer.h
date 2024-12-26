#pragma once
#include "Component.h"
#include "Renderer.h"
#include "appUtility.h"

class CRenderer :
    public Component
{


private:

    CSimpleSprite* sprite;
    Renderer::RenderLayer m_renderLayer;
    bool m_isShake;

public:

  

    CRenderer() : Component()
    {
        m_isShake = false;
        sprite = nullptr;
        m_renderLayer = Renderer::RenderLayer::Default;
        Renderer::AddRendererComponent(*this);
    }
    ~CRenderer() override
    {
        Renderer::RemoveRendererComponent(*this);
    }

    Renderer::RenderLayer GetRenderLayer()
    {
        return m_renderLayer;
    }

    void SetRenderLayer(Renderer::RenderLayer layer)
    {
        Renderer::RemoveRendererComponent(*this);
        m_renderLayer = layer;
        Renderer::AddRendererComponent(*this);
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

};

