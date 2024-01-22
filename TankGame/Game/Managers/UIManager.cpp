#include "stdafx.h"
#include "UIManager.h"

#include "GameManager.h"

UIManager::UIManager()
{
    controls = App::CreateSprite(".\\Resources\\Sprites\\controls_screen.png", 1, 1);
    controls->SetPosition(APP_VIRTUAL_WIDTH / 2.0f, APP_VIRTUAL_HEIGHT / 2.0f);
    controls->SetScale(0.66666f);
}

void UIManager::operator=(UIManager const&)
{
}

void UIManager::Draw()
{
    GameState gameState = GameManager::getInstance().gameState;

    if (gameState == GameState::STARTING)
    {
        controls->Draw();
        std::string drawPlayerCount = "Player Count: " + std::to_string(playerCount);
        App::Print((APP_VIRTUAL_WIDTH / 2.0f) - drawPlayerCount.size() * 4.0f, APP_VIRTUAL_HEIGHT / 2.0f, drawPlayerCount.c_str(), 1, 1, 1, GLUT_BITMAP_9_BY_15);
    }
    else if (gameState == GameState::PLAYING || gameState == GameState::GAMEOVER)
	{
        App::Print((APP_VIRTUAL_WIDTH / 2.0f) - centerMessage.size() * 4.0f, APP_VIRTUAL_HEIGHT / 2.0f, centerMessage.c_str(), 1, 1, 1, GLUT_BITMAP_9_BY_15);

        App::Print(10, APP_VIRTUAL_HEIGHT - 20, ("Turn: Player " + currentPlayer).c_str());
        App::Print(10, APP_VIRTUAL_HEIGHT - 40, ("Health: " + tankHealth).c_str());
        App::Print(10, APP_VIRTUAL_HEIGHT - 60, ("Fuel: " + tankFuel).c_str());
        App::Print(10, APP_VIRTUAL_HEIGHT - 80, ("Angle: " + turretAngle).c_str());
        App::Print(10, APP_VIRTUAL_HEIGHT - 100, ("Power: " + turretPower).c_str());
        App::Print(10, APP_VIRTUAL_HEIGHT - 120, ("Shell: " + selectedProjectile).c_str());

        App::Print(APP_VIRTUAL_WIDTH - 130, APP_VIRTUAL_HEIGHT - 20, "-Health-");
        
        for (int i = 0; i < playerCount; i++)
        {
            App::Print(APP_VIRTUAL_WIDTH - 130, APP_VIRTUAL_HEIGHT - 20 * (float)(i + 1.0f) - 20, ("Player " + std::to_string(i + 1) + ": " + tankHealthList[i]).c_str());
        }
    }
}

void UIManager::Destroy()
{
    tankHealthList.clear();
    delete controls;
}

void UIManager::SetPlayerCount(int count)
{
    playerCount = count;
}

void UIManager::SetCenterMessage(std::string msg)
{
    centerMessage = msg;
}

void UIManager::SetCurrentPlayer(int id)
{
    currentPlayer = std::to_string(id + 1);
}

void UIManager::SetTankHealth(float health, int tankId)
{
    tankHealth = std::to_string(health);
    tankHealth = tankHealth.substr(0, tankHealth.find("."));

    tankHealthList[tankId] = tankHealth;
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

void UIManager::SetSelectedProjectile(std::string projectile)
{
    selectedProjectile = projectile;
}

void UIManager::StartGame()
{
    tankHealthList.clear();
    for (int i = 0; i < PLAYER_COUNT_MAX; ++i)
    {
        std::string health = std::to_string(TANK_START_HEALTH);
        health = health.substr(0, health.find("."));
        tankHealthList.push_back(health);
    }
}
