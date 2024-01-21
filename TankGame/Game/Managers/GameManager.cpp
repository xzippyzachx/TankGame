#include "stdafx.h"
#include "GameManager.h"
#include "EntityManager.h"

#include "..\GameSettings.h"
#include "TerrainManager.h"
#include "UIManager.h"
#include "TurnManager.h"

#include "..\Entities\Tank.h"

GameManager::GameManager()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	UIManager::getInstance().SetPlayerCount(playerCount);
}

void GameManager::operator=(GameManager const&)
{
}

void GameManager::Update(float dt)
{
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_LEFT_SHOULDER, true))
	{
		glutFullScreenToggle();
	}

	if (gameState == GameState::STARTING)
	{
		if (App::GetController().CheckButton(XINPUT_GAMEPAD_X, true))
		{
			StartGame();
		}

		if (App::GetController().GetRightThumbStickY() > 0.25f)
		{
			ChangePlayerCount(true);
		}
		if (App::GetController().GetRightThumbStickY() < -0.25f)
		{
			ChangePlayerCount(false);
		}

		if (changeDelay > 0.0f)
		{
			changeDelay -= dt;
		}
		else if (changeDelay != 0.0f)
		{
			changeDelay = 0.0f;
		}
	}
	else if (gameState == GameState::PLAYING)
	{
		TerrainManager::getInstance().Update(dt);
		EntityManager::getInstance().Update(dt);
		TurnManager::getInstance().Update(dt);
	}
	else if (gameState == GameState::GAMEOVER)
	{
		TerrainManager::getInstance().Update(dt);
		EntityManager::getInstance().Update(dt);
		TurnManager::getInstance().Update(dt);

		if (App::GetController().CheckButton(XINPUT_GAMEPAD_X, true))
		{
			ResetGame();
			gameState = GameState::STARTING;
		}
	}
}

void GameManager::Draw()
{
	if (gameState == GameState::PLAYING || gameState == GameState::GAMEOVER)
	{
		TerrainManager::getInstance().Draw();
		EntityManager::getInstance().Draw();
	}
	UIManager::getInstance().Draw();
}

void GameManager::Destroy()
{
	TerrainManager::getInstance().Destroy();
	EntityManager::getInstance().Destroy();
	UIManager::getInstance().Destroy();
	TurnManager::getInstance().Destroy();
}

void GameManager::StartGame()
{
	gameState = GameState::PLAYING;

	// Backgound color
	glClearColor(0.518f, 0.8f, 1.0f, 1.0f);

	TerrainManager::getInstance().Generate();

	float space = (APP_VIRTUAL_WIDTH - 200.0f) / (playerCount - 1);
	float x = 100.0f;
	for (int i = 0; i < playerCount; i++)
	{
		Tank* newTank = EntityManager::getInstance().CreateTank();
		newTank->SetPosition(Vector2(x, 100.0f));

		x += space;
	}

	TurnManager::getInstance().NextTurn();
}

void GameManager::GameOver(int winner)
{
	gameState = GameState::GAMEOVER;

    UIManager::getInstance().SetCenterMessage("Game Over - Player " + std::to_string(winner + 1) + " Wins!");
}

void GameManager::ResetGame()
{
	EntityManager::getInstance().Reset();
	TerrainManager::getInstance().Reset();
	TurnManager::getInstance().Reset();
}

void GameManager::ChangePlayerCount(bool dir)
{
	if (changeDelay != 0.0f)
	{
		return;
	}
	changeDelay = 0.2f;

	playerCount += dir ? 1 : -1;
	if (playerCount <= 1)
	{
		playerCount = 2;
	}
	else if (playerCount > 4)
	{
		playerCount = 4;
	}

	UIManager::getInstance().SetPlayerCount(playerCount);
}
