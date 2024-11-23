#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"

using namespace std;

#define DELAY_CONST 100000

GameMechs *mainGameMechs;
Player *mainPlayer;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

int main(void)
{

    Initialize();

    while (!mainGameMechs->getExitFlagStatus())
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();
}

void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    mainGameMechs = new GameMechs();
    mainPlayer = new Player(mainGameMechs);
    mainGameMechs->generateFood(mainPlayer->getPlayerPos());
}

void GetInput(void)
{
    if (MacUILib_hasChar())
        mainGameMechs->setInput(MacUILib_getChar());
}

void RunLogic(void)
{
    mainPlayer->updatePlayerDir();
    mainPlayer->movePlayer();
}

void DrawScreen(void)
{
    MacUILib_clearScreen();
    MacUILib_printf("Snake Game\n");
    int i;
    for (i = 0; i < mainGameMechs->getBoardSizeY(); i++)
    {
        int j;
        for (j = 0; j < mainGameMechs->getBoardSizeX(); j++)
        {
            if (i == 0 || j == 0 || i == (mainGameMechs->getBoardSizeY() - 1) || j == (mainGameMechs->getBoardSizeX() - 1))
                MacUILib_printf("#");
            else
            {
                bool printed = false;
                for (int k = 0; k < mainPlayer->getPlayerPos()->getSize(); k++)
                {
                    if (mainPlayer->getPlayerPos()->getElement(k).pos->x == j && mainPlayer->getPlayerPos()->getElement(k).pos->y == i)
                    {
                        MacUILib_printf("%c", mainPlayer->getPlayerPos()->getHeadElement().getSymbol());
                        printed = true;
                    }
                }
                if (mainGameMechs->getFoodPos().pos->x == j && mainGameMechs->getFoodPos().pos->y == i)
                {
                    MacUILib_printf("%c", mainGameMechs->getFoodPos().getSymbol());
                    printed = true;
                }
                if (!printed)
                    MacUILib_printf(" ");
            }
        }
        MacUILib_printf("\n");
    }

    MacUILib_printf("Score: %d\n", mainGameMechs->getScore());
    if (mainGameMechs->getLoseFlagStatus())
        MacUILib_printf("You Lose");
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}

void CleanUp(void)
{
    delete mainGameMechs;
    delete mainPlayer;
    MacUILib_uninit();
}
