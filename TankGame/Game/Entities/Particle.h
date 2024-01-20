#pragma once
#include "Entity.h"
class Particle : public Entity
{
public:
    Particle();
	void Update(float dt) override;
    void Destroy() override;

	void SetSprite(char* fileName, Vector2 offset) override;
protected:

};

