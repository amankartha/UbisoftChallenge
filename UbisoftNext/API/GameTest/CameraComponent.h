#pragma once
#include "Component.h"
class CameraComponent :
    public Component
{
public:
    CameraComponent(GameObject* go) : Component(go) {}

    ~CameraComponent() {};

};

