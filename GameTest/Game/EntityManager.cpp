#include "stdafx.h"
#include "EntityManager.h"

EntityManager::EntityManager()
{
}

void EntityManager::Update(float dt)
{
	for (const auto& projectile : projectiles)
	{
		projectile->Update(dt);
	}
}

void EntityManager::Draw()
{
	for (const auto& projectile : projectiles)
	{
		projectile->Draw();
	}
}

void EntityManager::Destroy()
{
	projectiles.clear();
}

Projectile* EntityManager::CreateProjectile()
{
	Projectile* newProjectile = new Projectile();
	projectiles.push_back(newProjectile);

	return newProjectile;
}

void EntityManager::DestroyProjectile(Projectile* projectile)
{
	for (int i = 0; i < projectiles.size(); i++)
	{
		if (projectiles[i] == projectile)
		{
			projectiles.erase(projectiles.begin() + i);
			projectile->Destroy();
			return;
		}
	}
}