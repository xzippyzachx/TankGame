#include "stdafx.h"
#include "Particle.h"

#include "../Managers/EntityManager.h"

Particle::Particle() : Entity()
{
    SetSprite(".\\Resources\\Sprites\\shell_land.png", Vector2(0.0f, 0.0f));
}

void Particle::Update(float dt)
{
    Entity::Update(dt);

    if (GetSprite(0)->GetFrame() == 3)
    {
        EntityManager::getInstance().DestroyParticle(this);
    }
}

void Particle::Destroy()
{
    Entity::Destroy();
}

void Particle::SetSprite(char *fileName, Vector2 offset)
{
    CSimpleSprite* newSprite = App::CreateSprite(fileName, 4, 1);
	newSprite->SetScale(0.5f);
    newSprite->CreateAnimation(0, 0.005f / APP_MAX_FRAME_RATE, { 0, 1, 2, 3});
    newSprite->SetAnimation(0);

	sprites.push_back(newSprite);
	spriteOffsets.push_back(offset);
}
