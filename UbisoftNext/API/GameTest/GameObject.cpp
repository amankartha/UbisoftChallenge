#include "stdafx.h"
#include "GameObject.h"




void GameObject::Update()
{

	
	for (auto& pair : _components) {
		auto& type = pair.first;          
		auto& component = pair.second;   
		component->Update();             
	}
}
//
//void GameObject::Render()   moved to Renderer
//{
//	for (auto& pair : _components) {
//		auto& type = pair.first;
//		auto& component = pair.second;
//		component->Render();
//	}
//}

void GameObject::Init()
{
	for (auto& pair : _components) {
		auto& type = pair.first;
		auto& component = pair.second;
		component->Init();
	}
}
