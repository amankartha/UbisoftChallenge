#pragma once
#include "Component.h"
#include "PushDownAutomata.h"
class CPDAcontroller :
    public Component
{

private:
    AI::PushDownAutomata m_pda;
};

