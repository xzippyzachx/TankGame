#include "stdafx.h"
#include "Projectile.h"

#include <cmath>

#include "EntityManager.h"
#include "TerrainManager.h"

Projectile::Projectile() : Entity()
{
	SetSprite(".\\Resources\\Sprites\\tank_bullet1.png", Vector2(0.0f, 0.0f));
}

void Projectile::Update(float dt)
{
	Entity::Update(dt);

	SimulatePhysics(dt);
	UpdateAngle();
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
	
	if (position.y >= TerrainManager::getInstance().GetFloor(position.x))
	{
		//Gravity
		velocity.y -= 9.81f * dt * WORLD_SCALE;
	}
	else
	{
		velocity.y = 0.0f;
		velocity.x = 0.0f;

		TerrainManager::getInstance().Explode(position);
		EntityManager::getInstance().DestroyProjectile(this);
	}
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