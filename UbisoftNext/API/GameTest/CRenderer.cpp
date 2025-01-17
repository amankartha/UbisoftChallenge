#include "stdafx.h"
#include "CRenderer.h"
#include "Ctransform.h"
#include "GameObject.h"
#include "appUtility.h"
#include "Camera.h"

CRenderer::CRenderer(Renderer* renderer,RenderLayer layer ): m_main_renderer_(renderer)
{
	m_isShake = false;
	m_renderLayer = layer;
	//m_id = mainRenderer->AddRenderer(m_renderLayer);
	//mainRenderer->GetRenderable(m_renderLayer, m_id)->m_render_Function = [this](const Camera camera, bool isUI) { this->Render(camera, isUI); };
	
}

CRenderer::CRenderer(Renderer* renderer, bool turnOnImmediately, RenderLayer layer) : m_main_renderer_(renderer)
{
	m_isShake = false;
	m_renderLayer = layer;
	SetRendererOnOff(turnOnImmediately);
}

CRenderer::~CRenderer()
{
	m_main_renderer_->RemoveRenderer(m_renderLayer,m_id);
}

CSimpleSprite* CRenderer::GetSprite()
{
	return &m_main_renderer_->GetRenderable(m_renderLayer,m_id)->m_sprite;
}

void CRenderer::SetSprite(CSimpleSprite sprite)
{
	m_main_renderer_->GetRenderable(m_renderLayer, m_id)->SetSprite(sprite);
}

RenderLayer CRenderer::GetRenderLayer()
{
	return m_renderLayer;
}

//void CRenderer::SetRenderLayer(RenderLayer layer)  /
//{
//	m_isShake = false;
//	mainRenderer->RemoveRenderer(m_renderLayer,m_id);
//	m_renderLayer = layer;
//	m_id = mainRenderer->AddRenderer(layer);
//	mainRenderer->GetRenderable(m_renderLayer, m_id)->m_render_Function = [this](const Camera camera, bool isUI) { this->Render(camera, isUI); };
//}

void CRenderer::SetRendererOnOff(bool state)
{
	if (state)
	{
		m_id = m_main_renderer_->AddRenderer(m_renderLayer);
		m_main_renderer_->GetRenderable(m_renderLayer, m_id)->m_isOn = state;
		m_main_renderer_->GetRenderable(m_renderLayer, m_id)->m_renderable = this;
		//mainRenderer->GetRenderable(m_renderLayer, m_id)->m_render_Function = &CRenderer::Render;
	}
	else
	{
		m_main_renderer_->GetRenderable(m_renderLayer, m_id)->m_isOn = state;
		m_main_renderer_->RemoveRenderer(m_renderLayer, m_id);
		m_id = -1;
	}
}

void CRenderer::Shake(bool b)
{
	m_isShake = b;
}

void CRenderer::Update()
{
	if (m_enabled)
	{
		Ctransform* transform = &GetAttachedGameObject()->GetTransformComponent();
		
		GetSprite()->SetPosition(transform->GetWorldPosition().x , transform->GetWorldPosition().y );   //TODO: does this need to be called every time hmmmmmmmmmmm
		GetSprite()->SetScale(transform->GetScale());
	}
}

void CRenderer::Render(const Camera camera,bool isUI)
{
	if (isUI)
	{
		GetSprite()->Draw();
	}
	else
	{
		RenderWithCamera(camera.GetPosition(), camera.GetAngle(), camera.GetZoom());
	}
}



void CRenderer::RenderWithCamera(Vector2 offset,float a,float zoom) 
{
	float angleRadians = a * static_cast<float>(PI / 180.0);
	float cosAngle = cos(-angleRadians);
	float sinAngle = sin(-angleRadians);


	Vector2 currentPosition =  GetAttachedGameObject()->GetTransformComponent().GetWorldPosition();
	
	Vector2 relativePosition = currentPosition - offset ;


	Vector2 rotatedPosition = Vector2(cosAngle * (relativePosition.x) - sinAngle * (relativePosition.y),
										 sinAngle * (relativePosition.x) + cosAngle * (relativePosition.y)

	);

	Vector2 scaledPosition = rotatedPosition * zoom;

	Vector2 calculatedPosition = scaledPosition + Vector2(APP_VIRTUAL_WIDTH / 2, APP_VIRTUAL_HEIGHT / 2);

	//TODO DONT DRAW IF NOT ON SCREEN
	
	GetSprite()->SetScale(GetSprite()->GetScale() * zoom);

	GetSprite()->SetPosition(calculatedPosition.x , calculatedPosition.y);
	
	
	if (calculatedPosition.x >= 0 && calculatedPosition.x <= APP_VIRTUAL_WIDTH &&
		calculatedPosition.y >= 0 && calculatedPosition.y <= APP_VIRTUAL_HEIGHT) {
		GetSprite()->Draw();
	}

}





