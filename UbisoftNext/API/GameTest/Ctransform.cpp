#include "stdafx.h"
#include "Ctransform.h"
#include "GameObject.h"
#include "App/app.h"
void Ctransform::Update() 
{
	Component::Update();
	
}

void Ctransform::Render()
{
	App::Print(500, 500, (this->getAttachedGameObject()->name + "has a transform at" + std::to_string(x) + " " + std::to_string(y)).c_str());
}
