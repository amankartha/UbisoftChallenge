#include "stdafx.h"
#include "GameObject.h"


int GameObject::ID = 0;


void GameObject::Update()
{
	for (auto& pair : _components) {
		auto& type = pair.first;          
		auto& component = pair.second;   
		component->Update();             
	}
}

void GameObject::Render()
{
	for (auto& pair : _components) {
		auto& type = pair.first;
		auto& component = pair.second;
		component->Render();
	}
}

void GameObject::Init()
{
	for (auto& pair : _components) {
		auto& type = pair.first;
		auto& component = pair.second;
		component->Init();
	}
}
template <typename T, typename... Args>
void GameObject::AddComponent(Args&&... args)
{
	static_assert(std::is_base_of<Component, T>::value, "T must inherit from Component");  // This splits out an error on compile if I add something thats not a component
	components[std::type_index(typeid(T))] = std::make_shared<T>(std::forward<Args>(args)...); //make_shared is to make a shared_ptr and forward forwards the args to the constructor of the template

}
