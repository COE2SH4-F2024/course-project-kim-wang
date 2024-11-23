#include "GameMechs.h"
#include <stdlib.h>
#include <time.h>

GameMechs::GameMechs()
{
    boardSizeX = 30;
    boardSizeY = 15;
    exitFlag = false;
    loseFlag = false;
    score = 0;
    input = 0;
    srand(time(NULL));
    foodPos = objPos(0, 0, 'O');
}

GameMechs::GameMechs(int boardX, int boardY)
{
    boardSizeX = boardX;
    boardSizeY = boardY;
    exitFlag = false;
    loseFlag = false;
    score = 0;
    input = 0;
    srand(time(NULL));
}

// do you need a destructor?
GameMechs::~GameMechs()
{
}

bool GameMechs::getExitFlagStatus() const
{
    return exitFlag;
}

bool GameMechs::getLoseFlagStatus() const
{
    return loseFlag;
}

char GameMechs::getInput() const
{
    return input;
}

int GameMechs::getScore() const
{
    return score;
}

void GameMechs::incrementScore()
{
    score++;
}

int GameMechs::getBoardSizeX() const
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY() const
{
    return boardSizeY;
}

void GameMechs::setExitTrue()
{
    exitFlag = true;
}

void GameMechs::setLoseFlag()
{
    loseFlag = true;
}

void GameMechs::setInput(char this_input)
{
    input = this_input;
}

void GameMechs::clearInput()
{
    input = 0;
}

// More methods should be added here

void GameMechs::generateFood(objPosArrayList *playerPosArrayList)
{
    int xCheck[boardSizeX] = {0};
    int yCheck[boardSizeY] = {0};
    for (int i = 0; i < playerPosArrayList->getSize(); i++)
    {
        xCheck[playerPosArrayList->getElement(i).pos->x] = 0;
        yCheck[playerPosArrayList->getElement(i).pos->y] = 0;
    }
    bool foodMade = false;
    while (!foodMade)
    {
        int xPos = rand() % (boardSizeX - 2) + 1;
        int yPos = rand() % (boardSizeY - 2) + 1;
        if (xCheck[xPos] == 0 && yCheck[yPos] == 0)
        {
            foodPos.pos->x = xPos;
            foodPos.pos->y = yPos;
            foodMade = true;
        }
    }
}

objPos GameMechs::getFoodPos()
{
    return foodPos;
}
