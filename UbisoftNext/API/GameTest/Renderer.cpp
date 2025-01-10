#include "stdafx.h"
#include "Renderer.h"
#include "CRenderer.h"
#include "appUtility.h"
#include "Grid.h"
#include "Camera.h"
#include <algorithm>

//std::map<RenderLayer, std::vector<CRenderer*>> Renderer::RENDERMAP;


    void Renderer::RenderAll(Camera& currentCamera)
    {
        App::Print(1000, 300, std::to_string(m_rendermap_[RenderLayer::Default].size()).c_str());
        if (m_isShake)
        {
            m_shakeValue.x = FRAND_RANGE(-4, 4);
            m_shakeValue.y = FRAND_RANGE(-4, 4);
            for (const auto& [m_renderLayer, renderers] : m_rendermap_)
            {
             
                if (m_renderLayer == RenderLayer::UI)
                {
                    for (IRenderable* renderer : renderers)
                    {

                        renderer->Render(currentCamera,true);
                    }
                }
                else
                {
                    for (IRenderable* renderer : renderers)
                    {

                        renderer->Render(currentCamera);
                    }
                }
            }
        }
        else
        {
            for (const auto& [m_renderLayer, renderers] : m_rendermap_)
            {
                if (m_renderLayer == RenderLayer::UI)
                {
                    for (IRenderable* renderer : renderers)
                    {

                        renderer->Render(currentCamera,true);
                    }
                }
                else
                {
                    for (IRenderable* renderer : renderers)
                    {

                        renderer->Render(currentCamera);
                    }
                }
            }
        }
    }

    void Renderer::AddRenderer(IRenderable& renderer)
    {
        m_rendermap_[renderer.GetRenderLayer()].push_back(&renderer);
    }

    void Renderer::RemoveRenderer(IRenderable& renderer)
    {
        auto& renderVector = m_rendermap_[renderer.GetRenderLayer()];


        renderVector.erase(
            std::remove(renderVector.begin(), renderVector.end(), &renderer),
            renderVector.end()
        );
    }
    void Renderer::SetShake(bool b)
    {
        m_isShake = b;
    }
    void Renderer::SetShakeOff()
    {
        m_isShake = false;
    }

    void Renderer::DrawGridWithCamera(const Camera& camera, const GRID::GridSystem& gridSystem) const
    {
        Vector2 camPos = camera.GetPosition();
        Vector2 gridOrigin = gridSystem.GetOrigin();
        int cellSize = gridSystem.GetCellSize();
        IntVector2 gridSize = gridSystem.m_gridSize;

       
        Vector2 centeredOrigin = gridOrigin - Vector2(gridSize.x * cellSize / 2.0f, gridSize.y * cellSize / 2.0f);

       
        float gridWorldLeft = centeredOrigin.x;
        float gridWorldRight = centeredOrigin.x + gridSize.x * cellSize;
        float gridWorldTop = centeredOrigin.y;
        float gridWorldBottom = centeredOrigin.y + gridSize.y * cellSize;

  
        float camLeft = camPos.x - APP_VIRTUAL_WIDTH / 2.0f;
        float camRight = camPos.x + APP_VIRTUAL_WIDTH / 2.0f;
        float camTop = camPos.y - APP_VIRTUAL_HEIGHT / 2.0f;
        float camBottom = camPos.y + APP_VIRTUAL_HEIGHT / 2.0f;

       
        float startX = (std::max)(gridWorldLeft, std::floor(camLeft / cellSize) * cellSize);
        float endX = (std::min)(gridWorldRight, std::ceil(camRight / cellSize) * cellSize);
        float startY = (std::max)(gridWorldTop, std::floor(camTop / cellSize) * cellSize);
        float endY = (std::min)(gridWorldBottom, std::ceil(camBottom / cellSize) * cellSize);

        // Draw vertical grid lines
        for (float x = startX; x <= endX; x += cellSize)
        {
         
            float screenX = x - camPos.x + APP_VIRTUAL_WIDTH / 2.0f;

           
            float screenStartY = gridWorldTop - camPos.y + APP_VIRTUAL_HEIGHT / 2.0f;
            float screenEndY = gridWorldBottom - camPos.y + APP_VIRTUAL_HEIGHT / 2.0f;

            App::DrawLine(screenX, screenStartY, screenX, screenEndY);
        }

        // Draw horizontal grid lines
        for (float y = startY; y <= endY; y += cellSize)
        {
            
            float screenY = y - camPos.y + APP_VIRTUAL_HEIGHT / 2.0f;

           
            float screenStartX = gridWorldLeft - camPos.x + APP_VIRTUAL_WIDTH / 2.0f;
            float screenEndX = gridWorldRight - camPos.x + APP_VIRTUAL_WIDTH / 2.0f;

            App::DrawLine(screenStartX, screenY, screenEndX, screenY);
        }
    }

    


    

 
