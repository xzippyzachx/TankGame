#pragma once
#include "Entity.h"
class Projectile : public Entity
{
public:
	Projectile();
	void Update(float dt) override;
    void Destroy() override;

    void SetSprite(char* fileName, Vector2 offset) override;

    void SetVelocity(Vector2 vel);
protected:
    Vector2 velocity;

    void SimulatePhysics(float dt);
    void CheckHit();
    void UpdateAngle();
};

