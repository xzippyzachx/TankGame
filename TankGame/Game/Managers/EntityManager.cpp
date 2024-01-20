#include "stdafx.h"
#include "EntityManager.h"

EntityManager::EntityManager()
{
}

void EntityManager::operator=(EntityManager const&)
{
}

void EntityManager::Update(float dt)
{
	for (const auto& tank : tanks)
	{
		tank->Update(dt);
	}
	for (const auto& projectile : projectiles)
	{
		projectile->Update(dt);
	}
}

void EntityManager::Draw()
{
	for (const auto& tank : tanks)
	{
		tank->Draw();
	}
	for (const auto& projectile : projectiles)
	{
		projectile->Draw();
	}
}

void EntityManager::Destroy()
{
	tanks.clear();
	projectiles.clear();
}

Tank* EntityManager::CreateTank()
{
	Tank* newTank = new Tank();
	tanks.push_back(newTank);
	return newTank;
}

Projectile* EntityManager::CreateProjectile()
{
	Projectile* newProjectile = new Projectile();
	projectiles.push_back(newProjectile);
	return newProjectile;
}

void EntityManager::DestroyTank(Tank* tank)
{
	for (int i = 0; i < tanks.size(); i++)
	{
		if (tanks[i] == tank)
		{
			tanks.erase(tanks.begin() + i);
			tank->Destroy();
			return;
		}
	}
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