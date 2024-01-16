#pragma once
#include "Vector3.h"
#include "Component.h"

struct Transform : public Component
{
    Vector3 position, rotation, scale;
public:
    Transform();
    Transform(unsigned int entityId);
};

