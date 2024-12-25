#include "stdafx.h"
#include "CRenderer.h"
#include "Ctransform.h"
#include "GameObject.h"

void CRenderer::Update()
{
	if (enabled)
	{
		std::shared_ptr<Ctransform> transform = getAttachedGameObject().lock()->GetTransform();
		sprite->SetPosition(transform->GetPosition().x, transform->GetPosition().y);
	}
}

void CRenderer::Render()
{
	if (enabled)
	sprite->Draw();
}
