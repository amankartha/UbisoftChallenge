#pragma once
#include "Component.h"
#include "ObserverPattern.h"
class Ccursor :
    public Component
{

    
public:
    Ccursor(GameObject* gameObject) : Component(gameObject) {}
    void Init() override;
    void Update() override;
};

