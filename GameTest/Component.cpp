#include "stdafx.h"
#include "Component.h"

Component::Component()
{
}

Component::Component(unsigned int type, unsigned int entityId)
{
	this->type = type;
	this->entityId = entityId;
}
