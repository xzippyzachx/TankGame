#include "stdafx.h"
#include "Projectile.h"

#define _USE_MATH_DEFINES
#include <cmath>

#include "EntityManager.h"

Projectile::Projectile() : Entity()
{
	
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

void Projectile::SimulatePhysics(float dt)
{
	// Drag
	velocity.x *= 0.99f;

	position.x += velocity.x * dt * WORLD_SCALE;
	position.y += velocity.y * dt * WORLD_SCALE;
	
	if (position.y >= 100.0f)
	{
		//Gravity
		velocity.y -= 9.81f * dt * WORLD_SCALE;
	}
	else
	{
		velocity.y = 0.0f;
		velocity.x = 0.0f;
		position.y = 100.0f;

		EntityManager::getInstance().DestroyProjectile(this);
	}
}

void Projectile::UpdateAngle()
{
	if (velocity.GetMagnitude() == 0.0f)
	{
		return;
	}

	float angle = atan2(velocity.y, velocity.x); // Radians
	sprite->SetAngle(angle);
}

void Projectile::SetSprite(char* fileName)
{
	Entity::SetSprite(fileName);
}

void Projectile::SetVelocity(Vector2 vel)
{
	velocity = vel;
}