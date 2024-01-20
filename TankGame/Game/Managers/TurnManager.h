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
	void Destroy();

    int GetCurrentTurn() { return currentTurn; }
    void NextTurn();
    void NewTurn();
    
private:
	// Singlton pattern
	////////
	TurnManager();
	TurnManager(TurnManager const&);
    void operator=(TurnManager const&);
	////////

    int currentTurn = 0;
};

