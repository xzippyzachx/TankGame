#include "stdafx.h"
#include "Projectile.h"

#include <cmath>

#include "..\Managers\EntityManager.h"
#include "..\Managers\TerrainManager.h"
#include "..\Managers\TurnManager.h"

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

void Projectile::SetSprite(char* fileName, Vector2 offset)
{
	Entity::SetSprite(fileName, offset);
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
		part->SetPosition(position);
	}
	else if (hitTank != -1)
	{
		EntityManager::getInstance().GetTank(hitTank)->Damage(damage);
	}

	SetVelocity(Vector2(0.0f, 0.0f));

	TurnManager::getInstance().NextTurn();

	EntityManager::getInstance().DestroyProjectile(this);
}

int Projectile::CheckTankHit()
{
	if (armTime > 0.0f)
	{
		return -1;
	}

	for (int i = 0; i < PLAYER_COUNT; i++)
	{
		Tank* tank = EntityManager::getInstance().GetTank(i);
		if (position.Distance(tank->GetPosition()) < 15.0f)
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