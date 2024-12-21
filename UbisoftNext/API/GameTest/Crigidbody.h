#pragma once
#include "Component.h"
class Crigidbody :
    public Component
{
private:
    bool m_useGravity;
    Vector2 m_velocity;
    float m_bounciness;

};

