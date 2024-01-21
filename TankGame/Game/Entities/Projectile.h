#pragma once
#include "Entity.h"
#include "Tank.h"

class Projectile : public Entity
{
public:
	Projectile();
	void Update(float dt) override;
    void Destroy() override;

    void SetShotBy(Tank* tank) { tankShotBy = tank; }
    void SetVelocity(Vector2 vel);
protected:
    Tank* tankShotBy;

    Vector2 velocity;
    float damage = 25.0f;
    float armTime = 0.01f;

    void SimulatePhysics(float dt);
    void CheckHit();
    int CheckTankHit();
    void UpdateAngle();
};

