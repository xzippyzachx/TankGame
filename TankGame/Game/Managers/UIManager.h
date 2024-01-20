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

	void SetCurrentPlayer(int id);
    void SetTurretAngle(float angle);
    void SetTurretPower(float power);
private:
	// Singlton pattern
	////////
	UIManager();
	UIManager(UIManager const&);
    void operator=(UIManager const&);
	////////
	
	std::string currentPlayer;
    std::string tankAngle;
    std::string tankPower;
};

