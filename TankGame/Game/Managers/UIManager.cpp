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
    App::Print(10, APP_VIRTUAL_HEIGHT - 20, ("Player " + currentPlayer).c_str());
    App::Print(10, APP_VIRTUAL_HEIGHT - 40, ("Health: " + tankHealth).c_str());
    App::Print(10, APP_VIRTUAL_HEIGHT - 60, ("Angle: " + turretAngle).c_str());
    App::Print(10, APP_VIRTUAL_HEIGHT - 80, ("Power: " + turretPower).c_str());
}

void UIManager::Destroy()
{
}

void UIManager::SetCurrentPlayer(int id)
{
    currentPlayer = std::to_string(id + 1);
}

void UIManager::SetTankHealth(float health)
{
    tankHealth = std::to_string(health);
    tankHealth = tankHealth.substr(0, tankHealth.find("."));
}

void UIManager::SetTurretAngle(float angle)
{
    turretAngle = std::to_string(angle);
    turretAngle = turretAngle.substr(0, turretAngle.find("."));
}

void UIManager::SetTurretPower(float power)
{
    turretPower = std::to_string(power);
    turretPower = turretPower.substr(0, turretPower.find("."));
}