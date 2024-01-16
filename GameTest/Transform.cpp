#include "stdafx.h"
#include "Transform.h"

Transform::Transform()
{
	scale = Vector3(1.0f, 1.0f, 1.0f);
}

Transform::Transform(unsigned int entityId)
{
	Component(0, entityId);
	scale = Vector3(1.0f, 1.0f, 1.0f);
}
