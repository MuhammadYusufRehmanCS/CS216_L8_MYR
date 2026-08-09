// CS 216 Lab #8 Abstract
// Muhammad Yusuf Rehman

#ifndef GAME_H
#define GAME_H

#include "army.h"

#include <string>

class Game
{
public:
    Game();

    void playGame();

private:
    void battleArmies(Army &armyOne, Army &armyTwo);
    void battleCreatures(Creature &creatureOne, const std::string &armyOneName, Creature &creatureTwo, const std::string &armyTwoName, int creaturePosition);
    void attack(Creature &attacker, const std::string &attackerArmyName, Creature &defender, const std::string &defenderArmyName, int roundNumber);
    void printBattleHeader() const;
    void announceCreatureWinner(const Creature &creatureOne, const std::string &armyOneName, const Creature &creatureTwo, const std::string &armyTwoName, int roundCount) const;
    void announceArmyWinner(const Army &armyOne, const Army &armyTwo) const;
};

#endif