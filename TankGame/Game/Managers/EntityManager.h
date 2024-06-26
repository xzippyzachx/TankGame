#pragma once
#include "..\..\stdafx.h"
#include "..\..\app\app.h"

#include <vector>

#include "..\Entities\Tank.h"
#include "..\Entities\Projectile.h"
#include "..\Entities\Particle.h"

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
	void Reset();

	Tank* CreateTank();
	Projectile* CreateProjectile();
	Particle* CreateParticle();

	Tank* GetTank(int id);

	void DestroyTank(Tank* tank);
	void DestroyProjectile(Projectile* projectile);
	void DestroyParticle(Particle* particle);
private:
	// Singlton pattern
	////////
	EntityManager();
	EntityManager(EntityManager const&);
    void operator=(EntityManager const&);
	////////

	std::vector<Tank*> tanks;
	std::vector<Projectile*> projectiles;
	std::vector<Particle*> particles;
};

