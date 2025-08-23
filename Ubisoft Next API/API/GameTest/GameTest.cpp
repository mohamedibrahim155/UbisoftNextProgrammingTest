///////////////////////////////////////////////////////////////////////////////
// Filename: GameTest.cpp
// Provides a demo of how to use the API
///////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include <windows.h> 
#include <math.h>  
//------------------------------------------------------------------------
#include "app\app.h"
//------------------------------------------------------------------------
#include "src/World/World.h"



//------------------------------------------------------------------------
// Called before first update. Do any initial setup here.
//------------------------------------------------------------------------

World* world;

void Init()
{
	world = new World();
	world->start();
}

//------------------------------------------------------------------------
// Update your simulation here. deltaTime is the elapsed time since the last update in ms.
// This will be called at no greater frequency than the value of APP_MAX_FRAME_RATE
//------------------------------------------------------------------------
void Update(const float deltaTime)
{
	// Set global deltaTime
	Timer::GetInstance().deltaTime = (deltaTime /1000);
	world->update(deltaTime / 1000);
}

//------------------------------------------------------------------------
// Renders world's sprites and Texts
//------------------------------------------------------------------------
void Render()
{	
#pragma region WORLD_RENDER

	world->render();

#pragma endregion
}
//------------------------------------------------------------------------
// Add your shutdown code here. Called when the APP_QUIT_KEY is pressed.
// Just before the app exits.
//------------------------------------------------------------------------
void Shutdown()
{	
#pragma region Cleanups

	world->clean();

	delete world;

#pragma endregion

	
}