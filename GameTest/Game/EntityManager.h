#pragma once
#include "..\stdafx.h"
#include "..\app\app.h"

#include <vector>

#include "Projectile.h"

class EntityManager
{        
public:
	static EntityManager& getInstance()
	{
		static EntityManager instance;
		return instance;
	}
	
	void Update(float dt);
	void Draw();
	void Destroy();

	Projectile* CreateProjectile();
	void DestroyProjectile(Projectile* projectile);
private:
	EntityManager();
	EntityManager(EntityManager const&);
    void operator=(EntityManager const&);

	std::vector<Projectile*> projectiles;
};

