#pragma once
#include "Component.h"
#include "ObserverPattern.h"
class Ccursor :
    public Component
{
private:
    
public:
    Ccursor() : Component()
    {
       
    }
  
       
    void Init() override;
    void Update() override;
};

