#pragma once
#include "..\..\stdafx.h"
#include "..\..\app\app.h"

class TurnManager
{
public:
	// Singlton pattern
	////////
	static TurnManager& getInstance()
	{
		static TurnManager instance;
		return instance;
	}
	////////
    void Update(float dt);
	void Destroy();
    void Reset();

    int GetCurrentTurn();
    void NextTurn();
    void NewTurn();
private:
	// Singlton pattern
	////////
	TurnManager();
	TurnManager(TurnManager const&);
    void operator=(TurnManager const&);
	////////

    float turnDelay = 1.0f;

    int currentTurn = -1;

    int GetWinner();
};

