#include "stdafx.h"
#include "UIManager.h"

#include "GameManager.h"

UIManager::UIManager()
{
}

void UIManager::operator=(UIManager const&)
{
}

void UIManager::Draw()
{
    GameState gameState = GameManager::getInstance().gameState;

    if (gameState == GameState::STARTING)
    {
        App::Print((APP_VIRTUAL_WIDTH / 2.0f) - ("Player Count: " + playerCount).size() * 4.0f, APP_VIRTUAL_HEIGHT / 2.0f, ("Player Count: " + playerCount).c_str(), 1, 1, 1, GLUT_BITMAP_9_BY_15);
    }
    else if (gameState == GameState::PLAYING || gameState == GameState::GAMEOVER)
	{
        App::Print((APP_VIRTUAL_WIDTH / 2.0f) - centerMessage.size() * 4.0f, APP_VIRTUAL_HEIGHT / 2.0f, centerMessage.c_str(), 1, 1, 1, GLUT_BITMAP_9_BY_15);

        App::Print(10, APP_VIRTUAL_HEIGHT - 20, ("Player " + currentPlayer).c_str());
        App::Print(10, APP_VIRTUAL_HEIGHT - 40, ("Health: " + tankHealth).c_str());
        App::Print(10, APP_VIRTUAL_HEIGHT - 60, ("Fuel: " + tankFuel).c_str());
        App::Print(10, APP_VIRTUAL_HEIGHT - 80, ("Angle: " + turretAngle).c_str());
        App::Print(10, APP_VIRTUAL_HEIGHT - 100, ("Power: " + turretPower).c_str());
    }
}

void UIManager::Destroy()
{
}

void UIManager::SetPlayerCount(int count)
{
    playerCount = std::to_string(count);
}

void UIManager::SetCenterMessage(std::string msg)
{
    centerMessage = msg;
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

void UIManager::SetTankFuel(float fuel)
{
    tankFuel = std::to_string(fuel);
    tankFuel = tankFuel.substr(0, tankFuel.find("."));
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