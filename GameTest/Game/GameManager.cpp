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

#include "Player.h"
#include "Projectile.h"

Player* player;

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
	glClearColor(0.133f, 0.133f, 0.133f, 1.0f);

	
	player = new Player();
	player->SetSprite(".\\Resources\\Sprites\\tanks_tankGreen1.png");
	player->SetPosition(Vector2(APP_VIRTUAL_WIDTH / 2.0f, APP_VIRTUAL_HEIGHT / 2.0f));

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

	if (App::GetController().CheckButton(XINPUT_GAMEPAD_A, true))
	{
		Projectile* newProjectile = EntityManager::getInstance().CreateProjectile();
		newProjectile->SetSprite(".\\Resources\\Sprites\\tank_bullet1.png");
		newProjectile->SetPosition(Vector2(100, 100));
		newProjectile->SetVelocity(Vector2(50.0f, 50.0f));
	}

	player->Update(dt);

	EntityManager::getInstance().Update(dt);

	//------------------------------------------------------------------------
	// Sample Sound.
	//------------------------------------------------------------------------
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_B, true))
	{
		App::PlaySound(".\\Resources\\Audio\\Test.wav");
		glutFullScreen();
	}
}

//------------------------------------------------------------------------
// Add your display calls here (DrawLine,Print, DrawSprite.) 
// See App.h 
//------------------------------------------------------------------------
void Render()
{
	player->Draw();

	EntityManager::getInstance().Draw();

	//------------------------------------------------------------------------
	// Example Text.
	//------------------------------------------------------------------------
	App::Print(10, APP_VIRTUAL_HEIGHT - 20, "Player");

	//------------------------------------------------------------------------
	// Example Line Drawing.
	//------------------------------------------------------------------------
	/*
	static float a = 0.0f;
	float r = 1.0f;
	float g = 1.0f;
	float b = 1.0f;
	a += 0.1f;
	for (int i = 0; i < 20; i++)
	{

		float sx = 200 + sinf(a + i * 0.1f)*60.0f;
		float sy = 200 + cosf(a + i * 0.1f)*60.0f;
		float ex = 700 - sinf(a + i * 0.1f)*60.0f;
		float ey = 700 - cosf(a + i * 0.1f)*60.0f;
		g = (float)i / 20.0f;
		b = (float)i / 20.0f;
		App::DrawLine(sx, sy, ex, ey,r,g,b);
	}
	*/
}
//------------------------------------------------------------------------
// Add your shutdown code here. Called when the APP_QUIT_KEY is pressed.
// Just before the app exits.
//------------------------------------------------------------------------
void Shutdown()
{	
	player->Destroy();
	EntityManager::getInstance().Destroy();
}