#include "stdafx.h"
#include "app\app.h"

#include "Entity.h"

enum STATE
{
	IDLE,
	MOVE
};

class Player : public Entity
{
public:
	Player(const char* fileName, float posX, float posY);
	void Update(float dt) override;
protected:
	float speed = 0.25f;

};
