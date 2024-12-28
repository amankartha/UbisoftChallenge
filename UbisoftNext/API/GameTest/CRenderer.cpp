#include "stdafx.h"
#include "CRenderer.h"
#include "Ctransform.h"
#include "GameObject.h"
#include "appUtility.h"
void CRenderer::Update()
{
	if (enabled)
	{
		std::shared_ptr<Ctransform> transform = getAttachedGameObject()->GetTransform();
		
		sprite->SetPosition(transform->GetPosition().x, transform->GetPosition().y);   //TODO: does this need to be called every time hmmmmmmmmmmm
	}
}

void CRenderer::Render()
{
	if (enabled)
	{
		if (m_isShake)
		{
			sprite->SetPositionWithOffset(FRAND_RANGE(-1, 1), FRAND_RANGE(-1, 1));
			sprite->Draw();
		}
		else
		{
			sprite->Draw();
		}
	}
}

void CRenderer::Render(Vector2& offset)
{
	sprite->SetPositionWithOffset(offset.x, offset.y);
	sprite->Draw();
}

void CRenderer::RenderWithCamera(Vector2 offset)
{
	Vector2 calculatedPosition = getAttachedGameObject()->GetTransform()->GetPosition() - offset;

	//TODO DONT DRAW IF NOT ON SCREEN

	sprite->SetPosition(calculatedPosition.x, calculatedPosition.y);
	sprite->Draw();
}

