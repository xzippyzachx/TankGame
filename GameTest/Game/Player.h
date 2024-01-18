#include "..\stdafx.h"
#include "..\app\app.h"

#include "Entity.h"

enum STATE
{
	IDLE,
	MOVE
};

class Player : public Entity
{
public:
	Player();
	void Update(float dt) override;

	void SetSprite(char* fileName) override;
protected:
	float speed = 0.25f;

};
