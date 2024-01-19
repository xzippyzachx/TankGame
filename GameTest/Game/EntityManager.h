#pragma once
#include "..\stdafx.h"
#include "..\app\app.h"

#include <vector>

#include "Tank.h"
#include "Projectile.h"

class EntityManager
{        
public:
	// Singlton pattern
	////////
	static EntityManager& getInstance()
	{
		static EntityManager instance;
		return instance;
	}
	////////
	
	void Update(float dt);
	void Draw();
	void Destroy();

	Tank* CreateTank();
	Projectile* CreateProjectile();

	void DestroyTank(Tank* tank);
	void DestroyProjectile(Projectile* projectile);
private:
	// Singlton pattern
	////////
	EntityManager();
	EntityManager(EntityManager const&);
    void operator=(EntityManager const&);
	////////

	std::vector<Tank*> tanks;
	std::vector<Projectile*> projectiles;
};

