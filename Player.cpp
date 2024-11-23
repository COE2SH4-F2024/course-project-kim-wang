#include "Player.h"

Player::Player(GameMechs *thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    // mainGameMechsRef->getBoardSizeX() / 2, mainGameMechsRef->getBoardSizeY() / 2, '*')
    playerPosArrayList = new objPosArrayList();
    playerPosArrayList->insertHead(objPos(mainGameMechsRef->getBoardSizeX() / 2, mainGameMechsRef->getBoardSizeY() / 2, '*'));
}

Player::~Player()
{
    delete playerPosArrayList;
}

objPosArrayList *Player::getPlayerPos() const
{
    // return the reference to the playerPos arrray list
    return playerPosArrayList;
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic
    char input = mainGameMechsRef->getInput();
    if (input != 0) // if not null character
    {
        switch (input)
        {

        case ' ': // exit
            mainGameMechsRef->setExitTrue();
            break;
        case 'w':
            if (myDir == LEFT || myDir == RIGHT || myDir == STOP)
            {
                myDir = UP;
            }
            break;
        case 'd':
            if (myDir == UP || myDir == DOWN || myDir == STOP)
            {
                myDir = RIGHT;
            }
            break;
        case 's':
            if (myDir == LEFT || myDir == RIGHT || myDir == STOP)
            {
                myDir = DOWN;
            }
            break;
        case 'a':
            if (myDir == UP || myDir == DOWN || myDir == STOP)
            {
                myDir = LEFT;
            }
            break;

        default:
            break;
        }
    }
}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
    objPos newHead = (playerPosArrayList->getHeadElement());
    switch (myDir)
    {
    case UP:
        if (newHead.pos->y - 1 == 0)
            newHead = (objPos(newHead.pos->x, mainGameMechsRef->getBoardSizeY() - 2, '*'));
        else
            newHead = (objPos(newHead.pos->x, newHead.pos->y - 1, '*'));
        break;
    case RIGHT:
        if (newHead.pos->x + 1 == mainGameMechsRef->getBoardSizeX() - 1)
            newHead = (objPos(1, newHead.pos->y, '*'));
        else
            newHead = (objPos(newHead.pos->x + 1, newHead.pos->y, '*'));
        break;
    case DOWN:
        if (newHead.pos->y + 1 == mainGameMechsRef->getBoardSizeY() - 1)
            newHead = (objPos(newHead.pos->x, 1, '*'));
        else
            newHead = (objPos(newHead.pos->x, newHead.pos->y + 1, '*'));
        break;
    case LEFT:
        if (newHead.pos->x - 1 == 0)
            newHead = (objPos(mainGameMechsRef->getBoardSizeX() - 2, newHead.pos->y, '*'));
        else
            newHead = (objPos(newHead.pos->x - 1, newHead.pos->y, '*'));
        break;
    default:
        break;
    }
    if (myDir != STOP)
    {
        playerPosArrayList->insertHead(newHead);
        for (int i = 1; i < playerPosArrayList->getSize(); i++)
        {
            if (newHead.pos->x == playerPosArrayList->getElement(i).pos->x && newHead.pos->y == playerPosArrayList->getElement(i).pos->y)
            {
                mainGameMechsRef->setExitTrue();
                mainGameMechsRef->setLoseFlag();
            }
        }

        if (!(mainGameMechsRef->getFoodPos().pos->x == newHead.pos->x && mainGameMechsRef->getFoodPos().pos->y == newHead.pos->y))
            playerPosArrayList->removeTail();
        else
        {
            mainGameMechsRef->incrementScore();
            mainGameMechsRef->generateFood(playerPosArrayList);
        }
    }
}

// More methods to be added
