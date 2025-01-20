#include "stdafx.h"
#include "GridBlockGameObject.h"

#include "CRenderer.h"
#include "Crigidbody.h"
#include "Game.h"

class CRenderer;

GridBlockGameObject::GridBlockGameObject(Game* instance) : GameObject(instance)
{
	m_ctransform_ = AddComponent<Ctransform>();
	m_ctransform_->SetScale(0.60f);
  m_crigidbody_ =AddComponent<Crigidbody>(instance->GetPhysicsSimulation(), 50.0f, 50.0f, 0.3f, 0.8f, true, false);
  m_crenderer_ = AddComponent<CRenderer>(instance->GetRenderer());
  m_crigidbody_->ClearBody();
	
}

void GridBlockGameObject::Init()
{
	GameObject::Init();
}

void GridBlockGameObject::Update(float DeltaTime)
{
	GameObject::Update(DeltaTime);
}

void GridBlockGameObject::Render()
{
	GameObject::Render();
}

void GridBlockGameObject::Clear()
{
	m_crenderer_->SetRendererOnOff(false);
	m_crigidbody_->ClearBody();
}

void GridBlockGameObject::Start()
{
	m_crigidbody_->AddBody();
	m_crenderer_->SetRendererOnOff(true);
	m_crenderer_->SetSprite(*App::CreateSprite(".\\MiniGolfAssets\\tile_grey.png", 1, 1));
}
