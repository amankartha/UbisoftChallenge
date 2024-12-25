#pragma once
#include "Component.h"
#include "ObserverPattern.h"
class Ccursor :
    public Component
{
private:
    std::weak_ptr<Ctransform> m_transform;
public:
    Ccursor() : Component()
    {
       
    }
    ~Ccursor() override
    {

    }
       
    void Init() override;
    void Update() override;
};

