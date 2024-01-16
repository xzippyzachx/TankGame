#include "stdafx.h"
#include "app\app.h"

#include "Vector2.h"

class Entity
{
public:
	Entity();
	virtual void Update(float dt);
	void Draw();
	void Destroy();

	virtual void SetSprite(char* fileName);
	void SetPosition(Vector2 pos);
protected:
	CSimpleSprite* sprite;
	Vector2 position;

};