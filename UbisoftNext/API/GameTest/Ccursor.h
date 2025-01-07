#pragma once
#include "Component.h"
#include "ObserverPattern.h"
class Ccursor :
    public Component
{

    
public:
    
    void Init() override;
    void Update() override;
};

