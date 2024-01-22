#pragma once
#include "Entity.h"

class Tank : public Entity
{
public:
	Tank();
	void Update(float dt) override;
	static void Reset() { nextId = 0; deadAmount = 0; }

	int NextId() { nextId++; return nextId - 1; }
	int GetId() { return id; }

	void NewTurn();
	void EndTurn();
	void Damage(float amount);
	static int GetDeadAmount() { return deadAmount; }
	bool IsDead() { return dead; }
	void Winner();
	int GetShells() { return shells; }
	bool Collide(Vector2 pos);
protected:
	static int nextId;
	int id;

	float trackSpeed = 50.0f;
	float turretAngleSpeed = 30.0f;
	float turretPowerSpeed = 20.0f;

	float turretAngle = 150.0f;
	float turretPower = 50.0f;

	float fuel = TANK_START_FUEL;

	static int deadAmount;
	bool dead = false;
	float health = TANK_START_HEALTH;

	int shells = TANK_START_SHELLS;
	int selectedProjectile = 0;

	void ProcessInput(float dt);
	void Move(float dt, float inputX);
	void Angle(float dt, float inputX);
	void Power(float dt, float inputY);
	void SelectProjectile(int input);
	void Fire();
	void Die();
	void EngineSound(bool play);
	void TurretSound(bool play);
	void Highlight();
};
