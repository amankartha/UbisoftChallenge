#include "stdafx.h"
#include "Renderer.h"
#include "CRenderer.h"
#include "appUtility.h"

//std::map<RenderLayer, std::vector<CRenderer*>> Renderer::RENDERMAP;


    void Renderer::RenderAll(Transform currentCameraTransform,float zoom)
    {
        App::Print(1000, 300, std::to_string(RENDERMAP[RenderLayer::Default].size()).c_str());
        if (isShake)
        {
            shakeValue.x = FRAND_RANGE(-4, 4);
            shakeValue.y = FRAND_RANGE(-4, 4);
            for (const auto& [m_renderLayer, renderers] : RENDERMAP)
            {
             
                if (m_renderLayer == RenderLayer::UI)
                {
                    for (CRenderer* renderer : renderers)
                    {

                        renderer->Render();
                    }
                }
                else
                {
                    for (CRenderer* renderer : renderers)
                    {

                        renderer->RenderWithCamera(shakeValue + currentCameraTransform.position,currentCameraTransform.angle,zoom);
                    }
                }
            }
        }
        else
        {
            for (const auto& [m_renderLayer, renderers] : RENDERMAP)
            {
                if (m_renderLayer == RenderLayer::UI)
                {
                    for (CRenderer* renderer : renderers)
                    {

                        renderer->Render();
                    }
                }
                else
                {
                    for (CRenderer* renderer : renderers)
                    {

                        renderer->RenderWithCamera(currentCameraTransform.position, currentCameraTransform.angle,zoom);
                    }
                }
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
    void Renderer::SetShake(bool b)
    {
        isShake = b;
    }
    void Renderer::SetShakeOff()
    {
        isShake = false;
    }
