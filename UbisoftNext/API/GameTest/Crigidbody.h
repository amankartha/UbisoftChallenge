#pragma once
#include "Component.h"
#include "appUtility.h"

class Crigidbody :
    public Component
{
private:
    bool m_useGravity;
    Vector2 m_velocity;
    float m_bounciness;
public:
    Crigidbody()
    {

    }
    ~Crigidbody()
    {
        
    }
};

