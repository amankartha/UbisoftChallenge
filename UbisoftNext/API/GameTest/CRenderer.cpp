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

void CRenderer::RenderWithCamera(Vector2 offset,float a,float zoom) 
{
	float angleRadians = a * (PI / 180.0);
	float cosAngle = cos(angleRadians);
	float sinAngle = sin(angleRadians);


	Vector2 currentPosition =  getAttachedGameObject()->GetTransform()->GetPosition();
	
	Vector2 relativePosition = currentPosition - offset ;


	Vector2 rotatedPosition = Vector2(cosAngle * (relativePosition.x) - sinAngle * (relativePosition.y),
										 sinAngle * (relativePosition.x) + cosAngle * (relativePosition.y)

	);

	Vector2 scaledPosition = rotatedPosition * zoom;

	Vector2 calculatedPosition = scaledPosition + Vector2(APP_VIRTUAL_WIDTH / 2, APP_VIRTUAL_HEIGHT / 2);

	//TODO DONT DRAW IF NOT ON SCREEN
	
	sprite->SetScale(zoom);

	sprite->SetPosition(calculatedPosition.x , calculatedPosition.y );
	
	if (calculatedPosition.x >= 0 && calculatedPosition.x <= APP_VIRTUAL_WIDTH &&
		calculatedPosition.y >= 0 && calculatedPosition.y <= APP_VIRTUAL_HEIGHT) {
		sprite->Draw();
	}

}

//--------------------------------------------------------------------------------//



