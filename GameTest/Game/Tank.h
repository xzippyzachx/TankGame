#pragma once
#include "..\stdafx.h"
#include "..\app\app.h"

#include "Entity.h"

class Tank : public Entity
{
public:
	Tank();
	void Update(float dt) override;

	void SetSprite(char* fileName) override;
protected:
	float speed = 50.0f;

	void ProcessInput(float dt);
	void Move(float dt, float inputX);
	void Fire();
};
