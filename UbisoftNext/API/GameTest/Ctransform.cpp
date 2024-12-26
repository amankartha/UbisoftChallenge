#include "stdafx.h"
#include "Ctransform.h"
#include "GameObject.h"
#include "App/app.h"

int Ctransform::Count;

void Ctransform::Update() 
{
	Component::Update();
	
}

void Ctransform::Render()
{
	//App::Print(500, 100 + id * 20, (this->getAttachedGameObject()->name + "has a transform at" + m_position.Print()).c_str()); 
}
