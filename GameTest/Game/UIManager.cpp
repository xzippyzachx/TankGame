#include "stdafx.h"
#include "UIManager.h"

UIManager::UIManager()
{
}

void UIManager::operator=(UIManager const&)
{
}

void UIManager::Draw()
{
    App::Print(10, APP_VIRTUAL_HEIGHT - 20, "Player 1");
    App::Print(10, APP_VIRTUAL_HEIGHT - 40, ("Angle: " + tank1Angle).c_str());
    App::Print(10, APP_VIRTUAL_HEIGHT - 60, ("Power: " + tank1Power).c_str());
}

void UIManager::Destroy()
{
}

void UIManager::SetTurretAngle(int tankId, float angle)
{
    tank1Angle = std::to_string(angle);
    tank1Angle = tank1Angle.substr(0, tank1Angle.find("."));
}

void UIManager::SetTurretPower(int tankId, float power)
{
    tank1Power = std::to_string(power);
    tank1Power = tank1Power.substr(0, tank1Power.find("."));
}