#pragma once
#include <unordered_map>

class Entity
{
	unsigned int id;

public:
	Entity(unsigned int id);
	unsigned int GetId() { return id; }

};