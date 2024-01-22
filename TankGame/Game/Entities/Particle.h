#pragma once
#include "Entity.h"

struct ParticleType
{
    int id;
    std::string name;
    char* filename;
    int frameCount;
};

class Particle : public Entity
{
public:
    Particle();
	void Update(float dt) override;
    void Destroy() override;

    void SetupParticle(int type);
protected:
    ParticleType particleType;

    static std::vector<ParticleType> particleTypes;
};

