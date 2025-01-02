#include "stdafx.h"
#include "Renderer.h"
#include "CRenderer.h"
#include "appUtility.h"
#include "Grid.h"
#include "Camera.h"
#include <algorithm>

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

    void Renderer::DrawGridWithCamera(const Camera& camera, const GRID::GridSystem& gridSystem) const
    {
        Vector2 camPos = camera.GetPosition();
        Vector2 gridOrigin = gridSystem.GetOrigin();
        int cellSize = gridSystem.GetCellSize();
        IntVector2 gridSize = gridSystem.m_gridSize;

        // Grid boundaries in world space
        float gridWorldLeft = gridOrigin.x;
        float gridWorldRight = gridOrigin.x + gridSize.x * cellSize;
        float gridWorldTop = gridOrigin.y;
        float gridWorldBottom = gridOrigin.y + gridSize.y * cellSize;

        // Screen space boundaries of the camera
        float camLeft = camPos.x - APP_VIRTUAL_WIDTH / 2;
        float camRight = camPos.x + APP_VIRTUAL_WIDTH / 2;
        float camTop = camPos.y - APP_VIRTUAL_HEIGHT / 2;
        float camBottom = camPos.y + APP_VIRTUAL_HEIGHT / 2;

        // Determine the range of grid lines visible in the camera view
        float startX = (std::max)(gridWorldLeft, std::floor(camLeft / cellSize) * cellSize);
        float endX = (std::min)(gridWorldRight, std::ceil(camRight / cellSize) * cellSize);
        float startY =( std::max)(gridWorldTop, std::floor(camTop / cellSize) * cellSize);
        float endY = (std::min)(gridWorldBottom, std::ceil(camBottom / cellSize) * cellSize);

        for (float x = startX; x <= endX; x += cellSize)
        {
            // Convert world space to screen space
            float screenX = x - camPos.x + APP_VIRTUAL_WIDTH / 2;

            // Draw line only up to grid boundaries in world space (convert bounds to screen space)
            float screenStartY = (std::max)(0.0f, gridWorldTop - camPos.y + APP_VIRTUAL_HEIGHT / 2);
            float screenEndY = (std::min)((float)APP_VIRTUAL_HEIGHT, gridWorldBottom - camPos.y + APP_VIRTUAL_HEIGHT / 2);

            App::DrawLine(screenX, screenStartY, screenX, screenEndY);
        }

        // Draw horizontal grid lines
        for (float y = startY; y <= endY; y += cellSize)
        {
            // Convert world space to screen space
            float screenY = y - camPos.y + APP_VIRTUAL_HEIGHT / 2;

            // Draw line only up to grid boundaries in world space (convert bounds to screen space)
            float screenStartX = (std::max)(0.0f, gridWorldLeft - camPos.x + APP_VIRTUAL_WIDTH / 2);
            float screenEndX = (std::min)((float)APP_VIRTUAL_WIDTH, gridWorldRight - camPos.x + APP_VIRTUAL_WIDTH / 2);

            App::DrawLine(screenStartX, screenY, screenEndX, screenY);
        }
    }


    

 
