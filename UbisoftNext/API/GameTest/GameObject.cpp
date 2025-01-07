#include "stdafx.h"
#include "GameObject.h"




void GameObject::Update()
{

	
	for (auto& pair : m_components) {
		auto& type = pair.first;          
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
	App::remove(m_children, childObject);
}



Ctransform& GameObject::GetTransformComponent()
{
	return *this->GetComponent<Ctransform>();
}

void GameObject::Init()
{
	for (auto& pair : m_components) {
		auto& type = pair.first;
		auto& component = pair.second;
		component->Init();
	}
}
