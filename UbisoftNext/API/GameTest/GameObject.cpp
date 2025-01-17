#include "stdafx.h"
#include "GameObject.h"
#include "appUtility.h"



void GameObject::Update()
{
	for (auto& pair : m_components) {
		auto& component = pair.second;   
		component->Update();             
	}
}
//
//void GameObject::Render()   moved to Renderer
//{
//	for (auto& pair : m_components) {
//		auto& type = pair.first;
//		auto& component = pair.second;
//		component->Render();
//	}
//}

void GameObject::SetChild(GameObject* childObject)
{
	if (!childObject)
	{
		return;  //throw error here
	}

	if  (std::find(m_children.begin(), m_children.end(), childObject) == m_children.end())
	{
		m_children.push_back(childObject);
		childObject->m_parent = this;
	}
	else
	{
		//spit out error that child already exists!
	}
}

void GameObject::RemoveChild(GameObject* childObject)
{
	App::RemoveFromVector(m_children, childObject);
}

void GameObject::RemoveParent()
{
	GetTransformComponent().SetPosition(GetTransformComponent().GetWorldPosition());
	m_parent = nullptr;
}

void GameObject::SetParent(GameObject* parenteObject)
{
	GetTransformComponent().RecalculateWithNewParent(parenteObject);
	m_parent = parenteObject;
	parenteObject->SetChild(this);
}


Ctransform& GameObject::GetTransformComponent()
{
	//return *this->GetComponent<Ctransform>();
	auto* transform = dynamic_cast<Ctransform*>(m_components[std::type_index(typeid(Ctransform))].get());
	return *transform;
}

void GameObject::Init()
{
	for (auto& pair : m_components) {
		auto& type = pair.first;
		auto& component = pair.second;
		component->Init();
	}
}
