#pragma once
#include "Game.h"
class TestGame :
    public Game
{
    
public:
	 void InternalInit() override;
	 void InternalUpdate(const float deltaTime) override;
	 void InternalRender() override;
	 void InteralShutdown() override;

};

