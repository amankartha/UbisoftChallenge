#include "stdafx.h"
#include "CRenderer.h"
#include "Ctransform.h"
#include "GameObject.h"
#include "appUtility.h"
#include "Camera.h"
void CRenderer::Update()
{
	if (m_enabled)
	{
		Ctransform* transform = &getAttachedGameObject()->GetTransformComponent();
		
		sprite->SetPosition(transform->GetWorldPosition().x , transform->GetWorldPosition().y );   //TODO: does this need to be called every time hmmmmmmmmmmm
		sprite->SetScale(transform->GetScale());
	}
}

void CRenderer::Render(const Camera camera,bool isUI)
{
	if (isUI)
	{
		sprite->Draw();
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


	Vector2 currentPosition =  getAttachedGameObject()->GetTransformComponent().GetWorldPosition();
	
	Vector2 relativePosition = currentPosition - offset ;


	Vector2 rotatedPosition = Vector2(cosAngle * (relativePosition.x) - sinAngle * (relativePosition.y),
										 sinAngle * (relativePosition.x) + cosAngle * (relativePosition.y)

	);

	Vector2 scaledPosition = rotatedPosition * zoom;

	Vector2 calculatedPosition = scaledPosition + Vector2(APP_VIRTUAL_WIDTH / 2, APP_VIRTUAL_HEIGHT / 2);

	//TODO DONT DRAW IF NOT ON SCREEN
	
	sprite->SetScale(sprite->GetScale() * zoom);

	sprite->SetPosition(calculatedPosition.x , calculatedPosition.y);
	
	
	if (calculatedPosition.x >= 0 && calculatedPosition.x <= APP_VIRTUAL_WIDTH &&
		calculatedPosition.y >= 0 && calculatedPosition.y <= APP_VIRTUAL_HEIGHT) {
		sprite->Draw();
	}

}





