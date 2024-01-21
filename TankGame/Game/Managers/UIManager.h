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

	void SetCenterMessage(std::string msg);

	void SetCurrentPlayer(int id);
	void SetTankHealth(float health);
    void SetTurretAngle(float angle);
    void SetTurretPower(float power);
private:
	// Singlton pattern
	////////
	UIManager();
	UIManager(UIManager const&);
    void operator=(UIManager const&);
	////////

	std::string centerMessage;

	std::string currentPlayer;
	std::string tankHealth;
    std::string turretAngle;
    std::string turretPower;
};

