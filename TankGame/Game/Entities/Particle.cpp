#include "stdafx.h"
#include "Particle.h"

#include "../Managers/EntityManager.h"
#include <numeric>

Particle::Particle() : Entity()
{
}

void Particle::Update(float dt)
{
    Entity::Update(dt);

    if (GetSprite(0)->GetFrame() == frameCount - 1)
    {
        EntityManager::getInstance().DestroyParticle(this);
    }
}

void Particle::Destroy()
{
    Entity::Destroy();
}

void Particle::SetupParticle(ParticleType type)
{
    char* particleFilename;
	switch (type)
	{
		case ParticleType::SHELL_SMOKE:
			particleFilename = ".\\Resources\\Sprites\\shell_smoke.png";
            frameCount = 4;
			break;
		case ParticleType::TANK_EXPLODE:
			particleFilename =  ".\\Resources\\Sprites\\tank_explode.png";
            frameCount = 5;
			break;
        case ParticleType::TANK_SPARK:
			particleFilename =  ".\\Resources\\Sprites\\tank_spark.png";
            frameCount = 4;
			break;
        default:
			particleFilename = ".\\Resources\\Sprites\\shell_smoke.png";
			break;
	}
    SetSprite(particleFilename, Vector2(0.0f, 0.0f), frameCount);

    GetSprite(0)->SetScale(0.5f);

    std::vector<int> frames(frameCount);
    std::iota(std::begin(frames), std::end(frames), 0);
    GetSprite(0)->CreateAnimation(0, 0.005f / APP_MAX_FRAME_RATE, frames);
    GetSprite(0)->SetAnimation(0);
}
