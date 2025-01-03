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

    void RenderWithCamera(const Camera& camera,IRenderable renderable, )
    {

        float angleRadians = a * (PI / 180.0);
        float cosAngle = cos(-angleRadians);
        float sinAngle = sin(-angleRadians);


        Vector2 currentPosition = getAttachedGameObject()->GetTransform()->GetPosition();

        Vector2 relativePosition = currentPosition - offset;


        Vector2 rotatedPosition = Vector2(cosAngle * (relativePosition.x) - sinAngle * (relativePosition.y),
            sinAngle * (relativePosition.x) + cosAngle * (relativePosition.y)

        );

        Vector2 scaledPosition = rotatedPosition * zoom;

        Vector2 calculatedPosition = scaledPosition + Vector2(APP_VIRTUAL_WIDTH / 2, APP_VIRTUAL_HEIGHT / 2);

        //TODO DONT DRAW IF NOT ON SCREEN

        sprite->SetScale(sprite->GetScale() * zoom);

        sprite->SetPosition(calculatedPosition.x, calculatedPosition.y);


        if (calculatedPosition.x >= 0 && calculatedPosition.x <= APP_VIRTUAL_WIDTH &&
            calculatedPosition.y >= 0 && calculatedPosition.y <= APP_VIRTUAL_HEIGHT) {
            sprite->Draw();
        }

    }


    

 
