#pragma once
#include "..\..\stdafx.h"
#include "..\..\app\app.h"

#include <string>

class UIManager
{
public:
	// Singlton pattern
	////////
	static UIManager& getInstance()
	{
		static UIManager instance;
		return instance;
	}
	////////
	
	void Draw();
	void Destroy();

	void SetPlayerCount(int count);

	void SetCenterMessage(std::string msg);

	void SetCurrentPlayer(int id);
	void SetTankHealth(float health);
	void SetTankFuel(float fuel);
    void SetTurretAngle(float angle);
    void SetTurretPower(float power);

	void SetSelectedProjectile(std::string projectile);
private:
	// Singlton pattern
	////////
	UIManager();
	UIManager(UIManager const&);
    void operator=(UIManager const&);
	////////

	std::string playerCount;

	std::string centerMessage;

	std::string currentPlayer;
	std::string tankHealth;
	std::string tankFuel;
    std::string turretAngle;
    std::string turretPower;

	std::string selectedProjectile;

	CSimpleSprite* controls;
};

