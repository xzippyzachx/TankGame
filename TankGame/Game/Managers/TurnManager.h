#pragma once
#include "..\..\stdafx.h"
#include "..\..\app\app.h"

#include "..\GameSettings.h"

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

    float turnDelay = TIME_BETWEEN_TURNS;

    int currentTurn = -1;

    int GetWinner();
};

