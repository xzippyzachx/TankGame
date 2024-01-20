#pragma once
#include "..\stdafx.h"
#include "..\app\app.h"

#include "Entity.h"

class Tank : public Entity
{
public:
	Tank();
	void Update(float dt) override;

	void SetSprite(char* fileName, Vector2 offset) override;
protected:
	float trackSpeed = 50.0f;
	float turretAngleSpeed = 30.0f;
	float turretPowerSpeed = 20.0f;

	float turretAngle = 150.0f;
	float turretPower = 100.0f;

	void ProcessInput(float dt);
	void Move(float dt, float inputX);
	void Angle(float dt, float inputX);
	void Power(float dt, float inputY);
	void Fire();
};
