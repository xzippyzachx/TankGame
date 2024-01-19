#pragma once
#include "..\stdafx.h"
#include "..\app\app.h"

#include "..\math\Vector2.h"
#include "GameSettings.h"

class Entity
{
public:
	Entity();
	virtual void Update(float dt);
	void Draw();
	virtual void Destroy();

	virtual void SetSprite(char* fileName);
	void SetPosition(Vector2 pos);
protected:
	CSimpleSprite* sprite;
	Vector2 position;

};