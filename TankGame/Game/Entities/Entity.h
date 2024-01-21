#pragma once
#include "..\..\stdafx.h"
#include "..\..\app\app.h"

#include "..\..\math\Vector2.h"
#include "..\GameSettings.h"

class Entity
{
public:
	Entity();
	virtual void Update(float dt);
	void Draw();
	virtual void Destroy();

	virtual void SetSprite(char* fileName, Vector2 offset, int columns = 1);
	virtual CSimpleSprite* GetSprite(int spriteId);

	void SetPosition(Vector2 pos);
	Vector2 GetPosition() { return position; }
protected:
	std::vector<CSimpleSprite*> sprites;
	std::vector<Vector2> spriteOffsets;
	Vector2 position;
};