#pragma once
#include "Entity.h"
#include "Tank.h"

struct ProjectileType
{
    int id;
    std::string name;
    char* filename;
    char* soundFilename;
    float damage;
    float terrainRadius;
    int particleType;
};

class Projectile : public Entity
{
public:
	Projectile();
	void Update(float dt) override;
    void Destroy() override;

    void SetupProjectile(int type, Tank* tank);
    void SetVelocity(Vector2 vel);

    static ProjectileType GetProjectileType(int type) { return projectileTypes[type]; }
protected:
    ProjectileType projectileType;
    Tank* tankShotBy;

    Vector2 velocity;
    float armTime = 0.1f;

    void SimulatePhysics(float dt);
    void CheckHit();
    int CheckTankHit();
    void UpdateAngle();

    static std::vector<ProjectileType> projectileTypes;
};
