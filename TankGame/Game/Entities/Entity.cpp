#include "stdafx.h"
#include "..\..\app\app.h"

#include "Entity.h"

Entity::Entity()
{
	
}

void Entity::Update(float dt)
{
	for (const auto& sprite : sprites)
	{
		sprite->Update(dt);
	}
}

void Entity::Draw()
{
	int i = 0;
	for (const auto& sprite : sprites)
	{
		Vector2 offset = spriteOffsets[i];
		sprite->SetPosition(position.x + offset.x, position.y + offset.y);
		sprite->Draw();
		i++;
	}
	
	// Collider debug draw
	App::DrawLine(position.x - 20.0f, position.y, position.x + 20.0f, position.y, 1,0,0);
	App::DrawLine(position.x, position.y - 25.0f, position.x, position.y + 15.0f, 1,0,0);
}

void Entity::Destroy()
{
	sprites.clear();
	spriteOffsets.clear();
}

void Entity::SetSprite(char* fileName, Vector2 offset, int columns)
{
	CSimpleSprite* newSprite = App::CreateSprite(fileName, columns, 1);
	newSprite->SetScale(0.25f);
	sprites.push_back(newSprite);
	spriteOffsets.push_back(offset);
}

CSimpleSprite* Entity::GetSprite(int spriteId)
{
	return sprites[spriteId];
}

void Entity::SetPosition(Vector2 pos)
{
	position = pos;
}
