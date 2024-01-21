#pragma once
#include "Entity.h"
class Tank : public Entity
{
public:
	Tank();
	void Update(float dt) override;

	int NextId() { nextId++; return nextId - 1; }
	int GetId() { return id; }

	void NewTurn();
	void Damage(float amount);
	static int GetDeadAmount() { return deadAmount; }
protected:
	static int nextId;
	int id;

	float trackSpeed = 50.0f;
	float turretAngleSpeed = 30.0f;
	float turretPowerSpeed = 20.0f;

	float turretAngle = 150.0f;
	float turretPower = 50.0f;

	static int deadAmount;
	bool dead = false;
	float health = 100.0f;

	int shells = 1;

	void ProcessInput(float dt);
	void Move(float dt, float inputX);
	void Angle(float dt, float inputX);
	void Power(float dt, float inputY);
	void Fire();
	void EngineSound(bool play);
	void Die();
};
