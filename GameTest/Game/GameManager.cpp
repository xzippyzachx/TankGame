//------------------------------------------------------------------------
// GameTest.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include <windows.h>
#include <math.h>
//------------------------------------------------------------------------
#include "..\app\app.h"
//------------------------------------------------------------------------

#include "EntityManager.h"
#include "UIManager.h"

#include "Tank.h"
#include "Projectile.h"
#include "TerrainManager.h"

//------------------------------------------------------------------------
// Called before first update. Do any initial setup here.
//------------------------------------------------------------------------
void Init()
{
#ifdef _DEBUG
	// Init debug console
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);
#endif

	// Backgound color
	glClearColor(0.518f, 0.8f, 1.0f, 1.0f);

	Tank* newTank = EntityManager::getInstance().CreateTank();
	newTank->SetPosition(Vector2(APP_VIRTUAL_WIDTH / 2.0f, 100.0f));
}

//------------------------------------------------------------------------
// Update your simulation here. deltaTime is the elapsed time since the last update in ms.
// This will be called at no greater frequency than the value of APP_MAX_FRAME_RATE
//------------------------------------------------------------------------
void Update(float dt)
{
	dt = dt / 1000.0f;

	if (App::GetController().CheckButton(XINPUT_GAMEPAD_LEFT_SHOULDER, true))
	{
		glutFullScreenToggle();
	}

	TerrainManager::getInstance().Update(dt);
	EntityManager::getInstance().Update(dt);
}

//------------------------------------------------------------------------
// Add your display calls here (DrawLine,Print, DrawSprite.) 
// See App.h 
//------------------------------------------------------------------------
void Render()
{
	TerrainManager::getInstance().Draw();
	EntityManager::getInstance().Draw();
	UIManager::getInstance().Draw();
}
//------------------------------------------------------------------------
// Add your shutdown code here. Called when the APP_QUIT_KEY is pressed.
// Just before the app exits.
//------------------------------------------------------------------------
void Shutdown()
{
	TerrainManager::getInstance().Destroy();
	EntityManager::getInstance().Destroy();
	UIManager::getInstance().Destroy();
}