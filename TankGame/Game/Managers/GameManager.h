#pragma once
#include "..\..\stdafx.h"
#include "..\..\app\app.h"

enum GameState
{
    STARTING,
    PLAYING,
    GAMEOVER,
};

class GameManager
{
public:
    // Singlton pattern
	////////
	static GameManager& getInstance()
	{
		static GameManager instance;
		return instance;
	}
	////////
    
    void Update(float dt);
	void Draw();
	void Destroy();
    
    void GameOver(int winner);

    GameState gameState;

private:
    // Singlton pattern
	////////
	GameManager();
	GameManager(GameManager const&);
    void operator=(GameManager const&);
	////////

    void StartGame();
    void ResetGame();
};

