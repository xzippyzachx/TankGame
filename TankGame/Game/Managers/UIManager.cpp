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
    App::Print(10, APP_VIRTUAL_HEIGHT - 40, ("Angle: " + tankAngle).c_str());
    App::Print(10, APP_VIRTUAL_HEIGHT - 60, ("Power: " + tankPower).c_str());
}

void UIManager::Destroy()
{
}

void UIManager::SetCurrentPlayer(int id)
{
    currentPlayer = std::to_string(id + 1);
}

void UIManager::SetTurretAngle(float angle)
{
    tankAngle = std::to_string(angle);
    tankAngle = tankAngle.substr(0, tankAngle.find("."));
}

void UIManager::SetTurretPower(float power)
{
    tankPower = std::to_string(power);
    tankPower = tankPower.substr(0, tankPower.find("."));
}