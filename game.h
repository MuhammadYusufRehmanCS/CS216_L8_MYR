// CS 216 Lab #8 Abstract
// Muhammad Yusuf Rehman

#ifndef GAME_H
#define GAME_H

#include "army.h"

class Game
{
public:
    Game();

    void playGame();

private:
    void announceArmyWinner(const Army &armyOne, const Army &armyTwo) const;
};

#endif
