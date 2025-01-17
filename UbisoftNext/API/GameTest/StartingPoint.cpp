///////////////////////////////////////////////////////////////////////////////
// Filename: GameTest.cpp
// Provides a demo of how to use the API
// 
// I RENAMED THIS AND MADE IT CLEAER IT NOW ACTS AS THE STARTING POINT
// IDEALLY I WOULD SPLIT THE ENGINE INTO ANOTHER SOLUTION BUT I DIDN'T WANT TO DISRUPT THE FLOW GIVEN
///////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------
#include "stdafx.h"

#include "MiniGolfGame.h"


//TestGame GAME = TestGame();
MiniGolfGame GAME = MiniGolfGame();


void Init()
{
	GAME.InternalInit();
}
void Update(const float deltaTime)
{
	GAME.InternalUpdate(deltaTime);	
}
void Render()
{
	GAME.InternalRender();
}
void Shutdown()
{	
	GAME.InternalShutdown();
}