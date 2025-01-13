#pragma once
#include "Component.h"
#include "CustomMath.h"
#include "GameObject.h"
#include "PushDownAutomata.h"

class CAgent :
    public Component
{

    CAgent() : Component(), m_PDA(AI::Context()), m_transform_(this->getAttachedGameObject()->GetTransformComponent().GetTransform())
    {
    }

    ~CAgent(){}

private:
    AI::PushDownAutomata m_PDA;
    Transform* m_transform_ ;
};

