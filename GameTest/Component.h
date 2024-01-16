#pragma once

struct Component
{
	unsigned int type;
	unsigned int entityId;

public:
	Component();
	Component(unsigned int type, unsigned int entityId);
	unsigned int GetType() { return type; }
	unsigned int GetEntityId() { return entityId; }
};

