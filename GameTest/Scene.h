#pragma once
#include <vector>
#include "Component.h"

class Entity;
class Component;

class Scene
{
	// Entities
	std::vector<Entity> entities;

	// Components
	std::vector<std::vector<Component>> components;

	unsigned int nextId;

public:
	Scene();

	void Init();
	void Update(float dt);

	unsigned int CreateId();
	unsigned int CreateEntity();
	Component CreateComponent(unsigned int type, unsigned int entittyId);
	void DestroyEntity(unsigned int id);
};

