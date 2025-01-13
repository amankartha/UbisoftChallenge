#pragma once
#include "Component.h"
#include "appUtility.h"
#include "GameObject.h"

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
   
};

