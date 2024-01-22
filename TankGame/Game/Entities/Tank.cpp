#include "stdafx.h"
#include "..\..\app\app.h"

#include "..\Managers\EntityManager.h"
#include "..\Managers\UIManager.h"
#include "..\Managers\TerrainManager.h"
#include "..\Managers\TurnManager.h"

#include "Tank.h"
#include "Projectile.h"

int Tank::nextId = 0;
int Tank::deadAmount = 0;

Tank::Tank() : Entity()
{
	id = NextId();

	SetSprite(".\\Resources\\Sprites\\tanks_turret1.png", Vector2(-2.0f, 10.0f));
	SetSprite(".\\Resources\\Sprites\\tanks_tankTracks1.png", Vector2(0.0f, -10.0f));

	char* bodyFilename;
	switch (id)
	{
		case 0:
			bodyFilename = ".\\Resources\\Sprites\\tanks_tankGreen_body1.png";
			break;
		case 1:
			bodyFilename =  ".\\Resources\\Sprites\\tanks_tankNavy_body1.png";
			break;
		case 2:
			bodyFilename =  ".\\Resources\\Sprites\\tanks_tankDesert_body1.png";
			break;
		case 3:
			bodyFilename =  ".\\Resources\\Sprites\\tanks_tankGrey_body1.png";
			break;
		default:
			bodyFilename = ".\\Resources\\Sprites\\tanks_tankGreen_body1.png";
			break;
	}
	SetSprite(bodyFilename, Vector2(0.0f,0.0f));

	GetSprite(0)->SetAngle((-turretAngle * (PI / 180.0f)) + PI);
}

void Tank::Update(float dt)
{
	Entity::Update(dt);

	ProcessInput(dt);

	position.y = TerrainManager::getInstance().GetFloor(position.x) + 20.0f;

	if (position.y <= 0.0f)
	{
		Die();
	}
}

void Tank::NewTurn()
{
	if (dead)
	{
		TurnManager::getInstance().NextTurn();
	}

	shells = 1;
	fuel = 100.0f;

	UIManager::getInstance().SetTankHealth(health);
	UIManager::getInstance().SetTankFuel(fuel);
	UIManager::getInstance().SetTurretAngle(turretAngle);
	UIManager::getInstance().SetTurretPower(turretPower);
	UIManager::getInstance().SetSelectedProjectile(Projectile::GetProjectileType(selectedProjectile).name);

	Highlight();
}

void Tank::Damage(float amount)
{
	if (dead)
	{
		return;
	}

	health -= amount;
	if (health <= 0.0f)
	{
		Die();
	}

	UIManager::getInstance().SetTankHealth(health);

	App::PlaySound(".\\Resources\\Audio\\tank_hit.wav");
}

void Tank::Winner()
{
	shells = 1000;
	fuel = 1000.0f;
}

bool Tank::Collide(Vector2 pos)
{
    return pos.Distance(Vector2(position.x, position.y -5.0f)) < 20.0f;
}

void Tank::ProcessInput(float dt)
{
	if (TurnManager::getInstance().GetCurrentTurn() != id || dead)
	{
		return;
	}

	Move(dt, App::GetController().GetLeftThumbStickX());
	Angle(dt, App::GetController().GetRightThumbStickX());
	Power(dt, App::GetController().GetRightThumbStickY());

	if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_LEFT, true))
	{
		SelectProjectile(0);
	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_RIGHT, true))
	{
		SelectProjectile(1);
	}

	if (App::GetController().CheckButton(XINPUT_GAMEPAD_A, true))
	{
		Fire();
	}

	if (App::GetController().CheckButton(XINPUT_GAMEPAD_B, true))
	{
		Damage(25.0f);
	}
}

void Tank::Move(float dt, float inputX)
{
	// Dead zone
	if (!(inputX > 0.25f) && !(inputX < -0.25f))
	{
		EngineSound(false);
		return;
	}

	if (fuel <= 0.0f)
	{
		fuel = 0.0f;
		EngineSound(false);
		return;
	}
	fuel -= dt * 12.0f;

	if (position.x < 0)
	{
		position.x = 0;
		return;
	}
	else if (position.x > APP_VIRTUAL_WIDTH)
	{
		position.x = APP_VIRTUAL_WIDTH;
		return;
	}

	position.x += inputX * trackSpeed * dt;

	UIManager::getInstance().SetTankFuel(fuel);
	EngineSound(true);
}

void Tank::Angle(float dt, float inputX)
{
	// Dead zone
	if (!(inputX > 0.25f) && !(inputX < -0.25f))
	{
		TurretSound(false);
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
	UIManager::getInstance().SetTurretAngle(turretAngle);

	TurretSound(true);
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
		turretPower += inputY * turretPowerSpeed * dt;
	}
	else if (turretPower < 0.0f)
	{
		turretPower = 0.0f;
	}
	else
	{
		turretPower = 200.0f;
	}

	UIManager::getInstance().SetTurretPower(turretPower);
}

void Tank::SelectProjectile(int input)
{
	selectedProjectile = input;
	UIManager::getInstance().SetSelectedProjectile(Projectile::GetProjectileType(selectedProjectile).name);
}

void Tank::Fire()
{
	if (shells <= 0)
	{
		return;
	}
	shells--;

	Projectile* newProjectile = EntityManager::getInstance().CreateProjectile();
	newProjectile->SetupProjectile(selectedProjectile, this);
	newProjectile->SetPosition(Vector2(position.x - 2.0f, position.y + 10.0f));

	// std::cout << "Radians: " << turretAngle * (PI / 180.0f) <<"\n";
	Vector2 vel = Vector2(-cos(turretAngle * (PI / 180.0f)), sin(turretAngle * (PI / 180.0f))) * turretPower;
	// std::cout << "Vel: (" << vel.x << "," << vel.y <<")\n";
	newProjectile->SetVelocity(vel);

	App::PlaySound(".\\Resources\\Audio\\shell_fire.wav");
}

void Tank::Die()
{
	if (dead)
	{
		return;
	}
	dead = true;
	deadAmount++;
	health = 0.0f;

	Particle* part = EntityManager::getInstance().CreateParticle();
	part->SetupParticle(1);
	part->SetPosition(position);

	sprites.clear();
	spriteOffsets.clear();
	SetSprite(".\\Resources\\Sprites\\tanks_destroyed_body1.png", Vector2(0.0f,-10.0f));

	EngineSound(false);
	TurretSound(false);
	App::PlaySound(".\\Resources\\Audio\\tank_explosion.wav");

	if (TurnManager::getInstance().GetCurrentTurn() == id)
	{
		TurnManager::getInstance().NextTurn();
	}
}

void Tank::EngineSound(bool play)
{
	char* filename = ".\\Resources\\Audio\\tank_engine.wav";
	bool isPlaying = App::IsSoundPlaying(filename);
	if (play && !isPlaying)
	{
		App::PlaySound(filename, true);
	}
	else if (!play && isPlaying)
	{
		App::StopSound(filename);
	}
}

void Tank::TurretSound(bool play)
{
	char* filename = ".\\Resources\\Audio\\tank_turret.wav";
	bool isPlaying = App::IsSoundPlaying(filename);
	if (play && !isPlaying)
	{
		App::PlaySound(filename, true);
	}
	else if (!play && isPlaying)
	{
		App::StopSound(filename);
	}
}

void Tank::Highlight()
{
	Particle* part = EntityManager::getInstance().CreateParticle();
	part->SetupParticle(3);
	part->SetPosition(position);
}