#include "stdafx.h"
#include "Projectile.h"

#include <cmath>

#include "..\Managers\EntityManager.h"
#include "..\Managers\TerrainManager.h"
#include "..\Managers\TurnManager.h"
#include "..\Managers\GameManager.h"

Projectile::Projectile() : Entity()
{
	SetSprite(".\\Resources\\Sprites\\tank_bullet5.png", Vector2(0.0f, 0.0f));
}

void Projectile::Update(float dt)
{
	Entity::Update(dt);

	SimulatePhysics(dt);
	UpdateAngle();

	if (armTime >= 0.0f)
	{
		armTime -= dt;
	}
}

void Projectile::Destroy()
{
	Entity::Destroy();
}

void Projectile::SimulatePhysics(float dt)
{
	// Drag
	velocity.x *= 0.99f;

	position.x += velocity.x * dt * WORLD_SCALE;
	position.y += velocity.y * dt * WORLD_SCALE;

	velocity.y -= 9.81f * dt * WORLD_SCALE;
	
	CheckHit();
}

void Projectile::CheckHit()
{
	bool hitTerrain = position.y <= TerrainManager::getInstance().GetFloor(position.x);
	int hitTank = CheckTankHit();

	if (!hitTerrain && hitTank == -1)
	{
		return;
	}

	if (hitTerrain)
	{
		TerrainManager::getInstance().Explode(position);

		Particle* part = EntityManager::getInstance().CreateParticle();
		part->SetupParticle(ParticleType::SHELL_SMOKE);
		part->SetPosition(position);

		App::PlaySound(".\\Resources\\Audio\\shell_dirt.wav");
	}
	else if (hitTank != -1)
	{
		EntityManager::getInstance().GetTank(hitTank)->Damage(damage);

		Particle* part = EntityManager::getInstance().CreateParticle();
		part->SetupParticle(ParticleType::TANK_SPARK);
		part->SetPosition(position);
	}

	SetVelocity(Vector2(0.0f, 0.0f));

	if (tankShotBy->GetShells() <= 0)
	{
		TurnManager::getInstance().NextTurn();
	}

	EntityManager::getInstance().DestroyProjectile(this);
}

int Projectile::CheckTankHit()
{
	if (armTime > 0.0f)
	{
		return -1;
	}

	int playerCount = GameManager::getInstance().playerCount;
	for (int i = 0; i < playerCount; i++)
	{
		Tank* tank = EntityManager::getInstance().GetTank(i);

		if (tank->IsDead())
		{
			continue;
		}

		Vector2 tankPos = tank->GetPosition();
		if (position.Distance(Vector2(tankPos.x, tankPos.y -5.0f)) < 20.0f) // ToDo: Should really make a collider class that handles collisions
		{
			return tank->GetId();
		}
	}

	return -1;
}

void Projectile::UpdateAngle()
{
	if (velocity.Length() == 0.0f)
	{
		return;
	}

	float angle = atan2(velocity.y, velocity.x); // Radians
	GetSprite(0)->SetAngle(angle);
}

void Projectile::SetVelocity(Vector2 vel)
{
	velocity = vel;
}