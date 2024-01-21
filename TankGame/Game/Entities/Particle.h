#pragma once
#include "Entity.h"

enum ParticleType
{
    SHELL_SMOKE,
    TANK_EXPLODE,
    TANK_SPARK,
    TANK_HIGHLIGHT,
};

class Particle : public Entity
{
public:
    Particle();
	void Update(float dt) override;
    void Destroy() override;

    void SetupParticle(ParticleType type);
protected:
    int frameCount = 1;
};

