#pragma once
#include "Component.h"
#include "App/SimpleSprite.h"
#include "Renderer.h"

class CRenderer :
    public Component
{


private:

    CSimpleSprite* sprite;
    RenderLayer m_renderLayer;

public:

  

    CRenderer() : Component()
    {
        sprite = nullptr;
        m_renderLayer = RenderLayer::Default;
        Renderer::AddRendererComponent(*this);
    }
    ~CRenderer() override
    {
        Renderer::RemoveRendererComponent(*this);
    }

    RenderLayer GetRenderLayer()
    {
        return m_renderLayer;
    }

    void SetRenderLayer(RenderLayer layer)
    {
        Renderer::RemoveRendererComponent(*this);
        m_renderLayer = layer;
        Renderer::AddRendererComponent(*this);
    }



    void CreateSprite(const char* fileName,int columns, int rows)
    {
        sprite = App::CreateSprite(fileName, columns, rows);
    } 

    void Update() override;

    void Render() override;

};

