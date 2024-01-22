#include "stdafx.h"
#include "Particle.h"

#include "../Managers/EntityManager.h"
#include <numeric>

std::vector<ParticleType> Particle::particleTypes =
{
    {
        0,
        "Smoke",
        ".\\Resources\\Sprites\\shell_smoke.png",
        4,
    },
    {
        1,
        "Explode",
        ".\\Resources\\Sprites\\tank_explode.png",
        5,
    },
    {
        1,
        "Spark",
        ".\\Resources\\Sprites\\tank_spark.png",
        4,
    },
    {
        1,
        "Highlight",
        ".\\Resources\\Sprites\\tank_highlight.png",
        5,
    },
};

Particle::Particle() : Entity()
{
}

void Particle::Update(float dt)
{
    Entity::Update(dt);

    if (GetSprite(0)->GetFrame() == particleType.frameCount - 1)
    {
        EntityManager::getInstance().DestroyParticle(this);
    }
}

void Particle::Destroy()
{
    Entity::Destroy();
}

void Particle::SetupParticle(int type)
{
    particleType = particleTypes[type];
    SetSprite(particleType.filename, Vector2(0.0f, 0.0f), particleType.frameCount);

    GetSprite(0)->SetScale(0.5f);

    std::vector<int> frames(particleType.frameCount);
    std::iota(std::begin(frames), std::end(frames), 0);
    GetSprite(0)->CreateAnimation(0, 0.005f / APP_MAX_FRAME_RATE, frames);
    GetSprite(0)->SetAnimation(0);
}
