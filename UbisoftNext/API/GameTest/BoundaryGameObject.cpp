#include "stdafx.h"
#include "BoundaryGameObject.h"

#include "Crigidbody.h"
#include "Game.h"

BoundaryGameObject::BoundaryGameObject(Game* instance, int id, Vector2 position, float width, float height) :
GameObject(instance, id) , m_position(position), m_width(width), m_height(height)
{
}

void BoundaryGameObject::Init()
{
	GameObject::Init();
	AddComponent<Crigidbody>(GameInstance->GetPhysicsSimulation(), m_width,m_height ,0.3f, 0.8f, true);
	GetComponent<Ctransform>()->SetPosition(m_position);
}

void BoundaryGameObject::Update(float DeltaTime)
{
	GameObject::Update(DeltaTime);
}
