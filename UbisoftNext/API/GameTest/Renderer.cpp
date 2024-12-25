#include "stdafx.h"
#include "Renderer.h"
#include "CRenderer.h"


std::map<RenderLayer, std::vector<CRenderer*>> Renderer::RENDERMAP;

void Renderer::RenderAll()
{
    for (const auto& [m_renderLayer, renderers] : RENDERMAP) 
    {        
        for (CRenderer* renderer : renderers)
        {
            renderer->Render();
        }
    }
}

void Renderer::AddRendererComponent(CRenderer& renderer)
{
	RENDERMAP[renderer.GetRenderLayer()].push_back(&renderer);
}

void Renderer::RemoveRendererComponent(CRenderer& renderer)
{
    auto& renderVector = RENDERMAP[renderer.GetRenderLayer()];

   
    renderVector.erase(
        std::remove(renderVector.begin(), renderVector.end(), &renderer),
        renderVector.end()
    );
}
