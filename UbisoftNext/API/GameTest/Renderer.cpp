#include "stdafx.h"
#include "Renderer.h"
#include "CRenderer.h"
#include "appUtility.h"

//std::map<RenderLayer, std::vector<CRenderer*>> Renderer::RENDERMAP;
namespace Renderer
{
    void RenderAll()
    {

        if (isShake)
        {
            shakeValue.x = FRAND_RANGE(-4, 4);
            shakeValue.y = FRAND_RANGE(-4, 4);
            for (const auto& [m_renderLayer, renderers] : RENDERMAP)
            {
                for (CRenderer* renderer : renderers)
                {
                    renderer->Render(shakeValue);
                }
            }
        }
        else
        {
            for (const auto& [m_renderLayer, renderers] : RENDERMAP)
            {
                for (CRenderer* renderer : renderers)
                {
                    renderer->Render();
                }
            }
        }
    }

    void AddRendererComponent(CRenderer& renderer)
    {
        RENDERMAP[renderer.GetRenderLayer()].push_back(&renderer);
    }

    void RemoveRendererComponent(CRenderer& renderer)
    {
        auto& renderVector = RENDERMAP[renderer.GetRenderLayer()];


        renderVector.erase(
            std::remove(renderVector.begin(), renderVector.end(), &renderer),
            renderVector.end()
        );
    }
    void SetShake(bool b)
    {
        isShake = b;
    }
    void SetShakeOff()
    {
        isShake = false;
    }
}
