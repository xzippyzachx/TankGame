#include "stdafx.h"
#include "app\app.h"

class Entity
{
public:
	Entity(const char* fileName, float posX, float posY);
	virtual void Update(float dt);
	void Draw();
	void Destroy();
protected:
	CSimpleSprite* sprite;

};