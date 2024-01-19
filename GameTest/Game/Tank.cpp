#include "stdafx.h"
#include "..\app\app.h"

#include "EntityManager.h"

#include "Tank.h"
#include "Projectile.h"


Tank::Tank() : Entity()
{
	
}

void Tank::Update(float dt)
{
	Entity::Update(dt);

	ProcessInput(dt);
	
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_A, true))
	{
		Fire();
	}
}

void Tank::ProcessInput(float dt)
{
	float inputX = App::GetController().GetLeftThumbStickX();

	if (inputX > 0.25f || inputX < -0.25f)
	{
		position.x += inputX * speed * dt;
	}
}

void Tank::SetSprite(char* fileName)
{
	Entity::SetSprite(fileName);
}

void Tank::Fire()
{
	Projectile* newProjectile = EntityManager::getInstance().CreateProjectile();
	newProjectile->SetSprite(".\\Resources\\Sprites\\tank_bullet1.png");
	newProjectile->SetPosition(Vector2(position.x, position.y + 10.0f));
	newProjectile->SetVelocity(Vector2(50.0f, 50.0f));
}
