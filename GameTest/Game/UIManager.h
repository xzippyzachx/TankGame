#pragma once
#include "..\stdafx.h"
#include "..\app\app.h"

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

    void SetTurretAngle(int tankId, float angle);
    void SetTurretPower(int tankId, float power);
private:
	// Singlton pattern
	////////
	UIManager();
	UIManager(UIManager const&);
    void operator=(UIManager const&);
	////////

    std::string tank1Angle;
    std::string tank1Power;
};

