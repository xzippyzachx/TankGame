#include "stdafx.h"
#include "..\app\app.h"

#include "EntityManager.h"
#include "UIManager.h"

#include "Tank.h"
#include "Projectile.h"

Tank::Tank() : Entity()
{
	SetSprite(".\\Resources\\Sprites\\tanks_tankGreen_body1.png");

	UIManager::getInstance().SetTurretAngle(0, turretAngle);
}

void Tank::Update(float dt)
{
	Entity::Update(dt);

	ProcessInput(dt);
}

void Tank::SetSprite(char* fileName)
{
	Entity::SetSprite(fileName);
}

void Tank::ProcessInput(float dt)
{
	Move(dt, App::GetController().GetLeftThumbStickX());
	Angle(dt, App::GetController().GetLeftThumbStickY());

	if (App::GetController().CheckButton(XINPUT_GAMEPAD_A, true))
	{
		Fire();
	}
}

void Tank::Move(float dt, float inputX)
{
	// Dead zone
	if (!(inputX > 0.25f) && !(inputX < -0.25f))
	{
		return;
	}

	position.x += inputX * trackSpeed * dt;
}

void Tank::Angle(float dt, float inputY)
{
	// Dead zone
	if (!(inputY > 0.25f) && !(inputY < -0.25f))
	{
		return;
	}

	if (turretAngle >= 0.0f && turretAngle <= 180.0f)
	{
		turretAngle += -inputY * turretSpeed * dt;
	}
	else if (turretAngle < 0.0f)
	{
		turretAngle = 0.0f;
	}
	else
	{
		turretAngle = 180.0f;
	}

	UIManager::getInstance().SetTurretAngle(0, turretAngle);
}

void Tank::Fire()
{
	Projectile* newProjectile = EntityManager::getInstance().CreateProjectile();
	newProjectile->SetSprite(".\\Resources\\Sprites\\tank_bullet1.png");
	newProjectile->SetPosition(Vector2(position.x, position.y + 10.0f));

	// std::cout << "Radians: " << turretAngle * (PI / 180.0f) <<"\n";
	Vector2 vel = Vector2(-cos(turretAngle * (PI / 180.0f)), sin(turretAngle * (PI / 180.0f))) * 50.0f;
	// std::cout << "Vel: (" << vel.x << "," << vel.y <<")\n";
	newProjectile->SetVelocity(vel);
}
