#include "stdafx.h"
#include "app\app.h"

#include "Entity.h"

Entity::Entity(const char* fileName, float posX, float posY)
{
	sprite = App::CreateSprite(fileName, 2, 1);
	sprite->SetPosition(posX, posY);
	sprite->SetScale(5.0f);
}

void Entity::Update(float deltaTime)
{
	sprite->Update(deltaTime);
}

void Entity::Draw()
{
	sprite->Draw();
}

void Entity::Destroy()
{
	delete sprite;
}