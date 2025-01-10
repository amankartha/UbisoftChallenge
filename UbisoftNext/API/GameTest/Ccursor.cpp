#include "stdafx.h"
#include "Ccursor.h"
#include "GameObject.h"
#include "appUtility.h"
void Ccursor::Init()
{
	
}

void Ccursor::Update()
{
	getAttachedGameObject()->GetTransformComponent().SetPosition(App::GetMousePosVec2());
}
