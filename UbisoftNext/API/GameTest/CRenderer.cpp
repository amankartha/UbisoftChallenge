#include "stdafx.h"
#include "CRenderer.h"
#include "Ctransform.h"
#include "GameObject.h"

void CRenderer::Update()
{
	std::shared_ptr<Ctransform> transform = getAttachedGameObject()->GetComponent<Ctransform>();
	sprite->SetPosition(transform->x,transform->y);
}

void CRenderer::Render()
{
	sprite->Draw();
}
