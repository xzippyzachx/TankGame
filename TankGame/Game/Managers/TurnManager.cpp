#include "stdafx.h"
#include "TurnManager.h"
#include "..\GameSettings.h"

#include "EntityManager.h"
#include "UIManager.h"

#include "..\Entities\Tank.h"

TurnManager::TurnManager()
{
    NewTurn();
}

void TurnManager::operator=(TurnManager const &)
{
}

void TurnManager::Destroy()
{
}

void TurnManager::NextTurn()
{
    if (Tank::GetDeadAmount() >= PLAYER_COUNT - 1)
    {
        std::cout << "Game Over" << "\n";
        return;
    }

    currentTurn++;
    if (currentTurn == PLAYER_COUNT)
    {
        currentTurn = 0;
    }

    NewTurn();
}

void TurnManager::NewTurn()
{
    UIManager::getInstance().SetCurrentPlayer(currentTurn);

    Tank* tank = EntityManager::getInstance().GetTank(currentTurn);
    tank->NewTurn();
}
