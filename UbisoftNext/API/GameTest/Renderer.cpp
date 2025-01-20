#include "stdafx.h"
#include "Renderer.h"
#include "CRenderer.h"
#include "appUtility.h"
#include "Grid.h"
#include "Camera.h"
#include <algorithm>

#include "cameraManager.h"
#include "Game.h"

//std::map<RenderLayer, std::vector<CRenderer*>> Renderer::RENDERMAP;



void Renderer::RenderWithCamera(Vector2 offset, float a, float zoom ,std::vector<Vector2> worldPositions)
{
    float angleRadians = a * static_cast<float>(PI / 180.0);
    float cosAngle = cos(-angleRadians);
    float sinAngle = sin(-angleRadians);

    for (Vector2 worldPosition : worldPositions)
    {

        Vector2 currentPosition = worldPosition;

        Vector2 relativePosition = currentPosition - offset;


        Vector2 rotatedPosition = Vector2(cosAngle * (relativePosition.x) - sinAngle * (relativePosition.y),
            sinAngle * (relativePosition.x) + cosAngle * (relativePosition.y)

        );

        Vector2 scaledPosition = rotatedPosition * zoom;

        Vector2 calculatedPosition = scaledPosition + Vector2(APP_VIRTUAL_WIDTH / 2, APP_VIRTUAL_HEIGHT / 2);

        //TODO DONT DRAW IF NOT ON SCREEN

        m_gridFill_sprite->SetScale(m_gridFill_sprite->GetScale() * zoom);

        m_gridFill_sprite->SetPosition(calculatedPosition.x, calculatedPosition.y);


        if (calculatedPosition.x >= 0 && calculatedPosition.x <= APP_VIRTUAL_WIDTH &&
            calculatedPosition.y >= 0 && calculatedPosition.y <= APP_VIRTUAL_HEIGHT) {
            m_gridFill_sprite->Draw();
        }

        m_gridFill_sprite->SetScale(0.6f);
    }
}


void Renderer::RenderAll(Camera& currentCamera)   //todo:: this is slow must optimize
    {
        App::Print(1000, 300, std::to_string(m_rendermap_[RenderLayer::Default]->size()).c_str());
            m_shakeValue.x = FRAND_RANGE(-4, 4);
            m_shakeValue.y = FRAND_RANGE(-4, 4);
            for (const auto& element : m_rendermap_)
            {
                
                if (element.first == RenderLayer::UI)
                {
                    auto& pool = element.second;
                    for (size_t renderer : pool->activeIndices)
                    {
                      
                        pool->m_pool[renderer].obj.m_renderable->Render(currentCamera, true);
                       
                    }
                }
                else
                {

                    auto& pool = element.second;
                    for (size_t renderer : pool->activeIndices)
                    {

                        pool->m_pool[renderer].obj.m_renderable->Render(currentCamera, false);

                    }
                }
            }
    }


Renderer::Renderer(Game* instance)
{
    m_game_instance = instance;
    m_gridFill_sprite = App::CreateSprite(".\\MiniGolfAssets\\tile_grey.png", 1, 1);
    m_gridFill_sprite->SetScale(0.6f);

	for (int renderLayer = Background; renderLayer != end ; renderLayer++)
	{
		m_rendermap_[static_cast<RenderLayer>(renderLayer)] = std::make_unique<ObjectPool<Renderable>>(instance);
	}

	for (auto& layer : m_rendermap_)
	{
		layer.second.get()->InitializePool(100);
	}
		
	m_shakeValue = Vector2(0, 0);
	m_isShake = false;
}

Renderable* Renderer::GetRenderable(RenderLayer layer, size_t id)
{
    return m_rendermap_[layer]->GetDirect(id);
}

int Renderer::AddRenderer(RenderLayer layer)
{
   return m_rendermap_[layer]->Get()->m_index;
}

void Renderer::RemoveRenderer(RenderLayer layer,size_t id)
{
    m_rendermap_[layer]->Release(id);
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

void Renderer::DrawGridWithCameraAroundTransform(Ctransform* cameraTransform, const GRID::GridSystem& gridSystem,
	Ctransform* cursorTransform)
{
        Vector2 camPos = cameraTransform->GetWorldPosition();
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

        Vector2 cusorPosition = cursorTransform->GetWorldPosition() - Vector2(APP_VIRTUAL_WIDTH / 2.0f,APP_VIRTUAL_HEIGHT/2 ) + camPos;

		
        // Draw vertical grid lines
        for (float x = startX; x <= endX; x += cellSize)
        {
         
            float screenX = x - camPos.x + APP_VIRTUAL_WIDTH / 2.0f;

           
            float screenStartY = gridWorldTop - camPos.y + APP_VIRTUAL_HEIGHT / 2.0f;
            float screenEndY = gridWorldBottom - camPos.y + APP_VIRTUAL_HEIGHT / 2.0f;

            float distX = screenX - (cusorPosition.x - camPos.x + APP_VIRTUAL_WIDTH / 2.0f);
            if (distX * distX < 150 * 150)
            {
                float maxDistY = std::sqrt(150 * 150 - distX * distX);
                screenStartY = std::max(screenStartY, cusorPosition.y - maxDistY - camPos.y + APP_VIRTUAL_HEIGHT / 2.0f);
                screenEndY = std::min(screenEndY, cusorPosition.y + maxDistY - camPos.y + APP_VIRTUAL_HEIGHT / 2.0f);

                if (screenStartY <= screenEndY) 
                    App::DrawLine(screenX, screenStartY, screenX, screenEndY,0,0,1);
            }
        }

        // Draw horizontal grid lines
        for (float y = startY; y <= endY; y += cellSize)
        {
            
            float screenY = y - camPos.y + APP_VIRTUAL_HEIGHT / 2.0f;

            // Calculate screen X range for this Y and clamp to the circle
            float screenStartX = gridWorldLeft - camPos.x + APP_VIRTUAL_WIDTH / 2.0f;
            float screenEndX = gridWorldRight - camPos.x + APP_VIRTUAL_WIDTH / 2.0f;

            // Clamp the line within the circle
            float distY = screenY - (cusorPosition.y - camPos.y + APP_VIRTUAL_HEIGHT / 2.0f);
            if (distY * distY < 150 * 150)
            {
                float maxDistX = std::sqrt(150 * 150 - distY * distY);
                screenStartX = std::max(screenStartX, cusorPosition.x - maxDistX - camPos.x + APP_VIRTUAL_WIDTH / 2.0f);
                screenEndX = std::min(screenEndX, cusorPosition.x + maxDistX - camPos.x + APP_VIRTUAL_WIDTH / 2.0f);

                if (screenStartX <= screenEndX) // Only draw if inside circle
                    App::DrawLine(screenStartX, screenY, screenEndX, screenY,0,0,1);
            }
        }
}

void Renderer::DrawFilledCells(const GRID::GridSystem& gridSystem)
{
    std::vector<Vector2> positions = gridSystem.GetAllFilledCells();
    Camera* maincam = &m_game_instance->GetCameraManager()->GetMainCamera();
    RenderWithCamera(maincam->GetPosition(), maincam->GetAngle(), maincam->GetZoom(), positions);
}



    


    

 
