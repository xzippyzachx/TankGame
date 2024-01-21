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
			StartGame();
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

	float space = (APP_VIRTUAL_WIDTH - 200.0f) / (PLAYER_COUNT - 1);
	float x = 100.0f;
	for (int i = 0; i < PLAYER_COUNT; i++)
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
