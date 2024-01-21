#include "stdafx.h"
#include "TurnManager.h"
#include "..\GameSettings.h"

#include "EntityManager.h"
#include "UIManager.h"
#include "GameManager.h"

#include "..\Entities\Tank.h"

TurnManager::TurnManager()
{
}

void TurnManager::operator=(TurnManager const &)
{
}

void TurnManager::Update(float dt)
{
    if (turnDelay > 0.0f) // ToDo: This delaying should really be done on a diff thread
    {
        turnDelay -= dt;
    }
    else if (turnDelay != 0.0f)
    {
        turnDelay = 0.0f;
        NewTurn();
    }
}

void TurnManager::Destroy()
{
}

void TurnManager::Reset()
{
    currentTurn = -1;
}

int TurnManager::GetCurrentTurn()
{
    if (turnDelay > 0.0f)
    {
        return -1;
    }

    return currentTurn;
}

void TurnManager::NextTurn()
{
    if (Tank::GetDeadAmount() >= PLAYER_COUNT - 1)
    {
        currentTurn = GetWinner();
        UIManager::getInstance().SetCurrentPlayer(currentTurn);
        GameManager::getInstance().GameOver(currentTurn);
        EntityManager::getInstance().GetTank(currentTurn)->Winner();
        return;
    }

    do
    {
        currentTurn++;
        if (currentTurn == PLAYER_COUNT)
        {
            currentTurn = 0;
        }
    }
    while (EntityManager::getInstance().GetTank(currentTurn)->IsDead()); // Skip dead players

    UIManager::getInstance().SetCenterMessage("Player " + std::to_string(currentTurn + 1) + " Turn");
    
    turnDelay = 1.0f;
}

void TurnManager::NewTurn()
{
    UIManager::getInstance().SetCenterMessage("");
    UIManager::getInstance().SetCurrentPlayer(currentTurn);

    EntityManager::getInstance().GetTank(currentTurn)->NewTurn();
}

int TurnManager::GetWinner()
{
    for (int i = 0; i < PLAYER_COUNT; i++)
	{
        Tank* tank = EntityManager::getInstance().GetTank(i);
        if (!tank->IsDead())
        {
            return i;
        }
    }
    return 0;
}
