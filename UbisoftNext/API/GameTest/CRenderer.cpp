#include "stdafx.h"
#include "CRenderer.h"
#include "Ctransform.h"
#include "GameObject.h"

void CRenderer::Update()
{
	if (enabled)
	{
		std::shared_ptr<Ctransform> transform = getAttachedGameObject()->GetComponent<Ctransform>();
		sprite->SetPosition(transform->position.x,transform->position.y);
	}
}

void CRenderer::Render()
{
	if (enabled)
	sprite->Draw();
}
