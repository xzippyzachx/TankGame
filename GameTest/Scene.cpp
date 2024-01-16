#include "stdafx.h"
#include "Scene.h"
#include "Entity.h";

#include "Transform.h"

Scene::Scene()
{
}

void Scene::Init()
{
	nextId = 0;

	components = std::vector<std::vector<Component>>(1);
}

void Scene::Update(float dt)
{

}

unsigned int Scene::CreateId()
{
	nextId++;
	return nextId - 1;
}

unsigned int Scene::CreateEntity()
{
	unsigned int newId = CreateId();
	entities.push_back(Entity(newId));
		
	for (int i = 0; i < components.size(); i++)
	{
		components[i].push_back(CreateComponent(i, newId));
	}

	return newId;
}

Component Scene::CreateComponent(unsigned int type, unsigned int entittyId)
{
	switch (type)
	{
		case 0:
			return Transform(entittyId);
		default:
			return Component();
	}
}

void Scene::DestroyEntity(unsigned int id)
{
}
