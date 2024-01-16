#include "stdafx.h"
#include "app\app.h"

#include "Entity.h"

Entity::Entity()
{
	
}

void Entity::Update(float deltaTime)
{
	sprite->Update(deltaTime);
}

void Entity::Draw()
{
	sprite->SetPosition(position.x, position.y);
	sprite->Draw();
}

void Entity::Destroy()
{
	delete sprite;
}

void Entity::SetSprite(char* fileName)
{
	sprite = App::CreateSprite(fileName, 2, 1);
	sprite->SetScale(5.0f);
}

void Entity::SetPosition(Vector2 pos)
{
	position = pos;
}
