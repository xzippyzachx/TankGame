#include "stdafx.h"
#include "Projectile.h"

#include <cmath>

#include "..\Managers\EntityManager.h"
#include "..\Managers\TerrainManager.h"
#include "..\Managers\TurnManager.h"
#include "..\Managers\GameManager.h"

std::vector<ProjectileType> Projectile::projectileTypes =
{
    {
        0,
        "Regular",
        ".\\Resources\\Sprites\\tank_bullet5.png",
		".\\Resources\\Audio\\shell_dirt.wav",
        34.0f,
        20.0f,
		0,
    },
    {
        1,
        "Explosive",
        ".\\Resources\\Sprites\\tank_bullet3.png",
		".\\Resources\\Audio\\tank_explosion.wav",
        25.0f,
        50.0f,
		1,
    },
};

Projectile::Projectile() : Entity()
{
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

void Projectile::SetupProjectile(int type, Tank* tank)
{
	projectileType = projectileTypes[type];
	SetSprite(projectileType.filename, Vector2(0.0f, 0.0f));

	tankShotBy = tank;
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
		TerrainManager::getInstance().Explode(position, projectileType.terrainRadius);

		Particle* part = EntityManager::getInstance().CreateParticle();
		part->SetupParticle(projectileType.particleType);
		part->SetPosition(position);

		App::PlaySound(projectileType.soundFilename);
	}
	else if (hitTank != -1)
	{
		TerrainManager::getInstance().Explode(position, projectileType.terrainRadius);

		EntityManager::getInstance().GetTank(hitTank)->Damage(projectileType.damage);

		Particle* part = EntityManager::getInstance().CreateParticle();
		part->SetupParticle(2);
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
	int playerCount = GameManager::getInstance().playerCount;
	for (int i = 0; i < playerCount; i++)
	{
		Tank* tank = EntityManager::getInstance().GetTank(i);

		if (tank->IsDead())
		{
			continue;
		}

		if (tank->GetId() == tankShotBy->GetId() && armTime > 0.0f)
		{
			continue;
		}

		if (tank->Collide(position))
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