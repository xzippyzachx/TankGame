#include "stdafx.h"
#include "..\app\app.h"

#include "EntityManager.h"
#include "UIManager.h"

#include "Tank.h"
#include "Projectile.h"

Tank::Tank() : Entity()
{
	SetSprite(".\\Resources\\Sprites\\tanks_turret1.png", Vector2(-2.0f, 10.0f));
	SetSprite(".\\Resources\\Sprites\\tanks_tankTracks1.png", Vector2(0.0f, -10.0f));

	SetSprite(".\\Resources\\Sprites\\tanks_tankGreen_body1.png", Vector2(0.0f,0.0f));

	GetSprite(0)->SetAngle((-turretAngle * (PI / 180.0f)) + PI);
	UIManager::getInstance().SetTurretAngle(0, turretAngle);
	UIManager::getInstance().SetTurretPower(0, turretPower);
}

void Tank::Update(float dt)
{
	Entity::Update(dt);

	ProcessInput(dt);
}

void Tank::SetSprite(char* fileName, Vector2 offset)
{
	Entity::SetSprite(fileName, offset);
}

void Tank::ProcessInput(float dt)
{
	Move(dt, App::GetController().GetLeftThumbStickX());
	Angle(dt, App::GetController().GetRightThumbStickX());
	Power(dt, App::GetController().GetRightThumbStickY());

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

void Tank::Angle(float dt, float inputX)
{
	// Dead zone
	if (!(inputX > 0.25f) && !(inputX < -0.25f))
	{
		return;
	}

	if (turretAngle >= 0.0f && turretAngle <= 180.0f)
	{
		turretAngle += inputX * turretAngleSpeed * dt;
	}
	else if (turretAngle < 0.0f)
	{
		turretAngle = 0.0f;
	}
	else
	{
		turretAngle = 180.0f;
	}

	GetSprite(0)->SetAngle((-turretAngle * (PI / 180.0f)) + PI);
	UIManager::getInstance().SetTurretAngle(0, turretAngle);
}

void Tank::Power(float dt, float inputY)
{
	// Dead zone
	if (!(inputY > 0.25f) && !(inputY < -0.25f))
	{
		return;
	}

	if (turretPower >= 0.0f && turretPower <= 200.0f)
	{
		turretPower += -inputY * turretPowerSpeed * dt;
	}
	else if (turretPower < 0.0f)
	{
		turretPower = 0.0f;
	}
	else
	{
		turretPower = 200.0f;
	}

	UIManager::getInstance().SetTurretPower(0, turretPower);
}

void Tank::Fire()
{
	Projectile* newProjectile = EntityManager::getInstance().CreateProjectile();
	newProjectile->SetPosition(Vector2(position.x - 2.0f, position.y + 10.0f));

	// std::cout << "Radians: " << turretAngle * (PI / 180.0f) <<"\n";
	Vector2 vel = Vector2(-cos(turretAngle * (PI / 180.0f)), sin(turretAngle * (PI / 180.0f))) * turretPower;
	// std::cout << "Vel: (" << vel.x << "," << vel.y <<")\n";
	newProjectile->SetVelocity(vel);

	App::PlaySound(".\\Resources\\Audio\\shell_fire.wav");
}
