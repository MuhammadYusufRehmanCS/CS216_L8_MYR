// CS 216 Lab #8 Abstract
// Muhammad Yusuf Rehman

#ifndef ARMY_H
#define ARMY_H

#include "creature.h"

#include <fstream>
#include <string>

class Army
{
private:
    std::string name = DEFAULT_ARMY_NAME;
    int size = 0;
    Creature **ppCreatures = nullptr;

public:
    Army();
    Army(const Army &rhsArmy);
    Army(const std::string &armyName, int armySize);
    Army(const std::string &armyName, int armySize, std::ifstream &nameFile);
    ~Army();

    Army &operator=(const Army &rhsArmy);

    bool isGenerated() const;
    const std::string &getName() const;
    int getTotalHealth() const;

    void battle(Army &opponentArmy);
    void print(const std::string &heading) const;

private:
    void setArmy(const std::string &armyName, int armySize, Creature **&ppNewCreatures);
    void generateCreatures(std::ifstream &nameFile);
    bool createCreatureArray(Creature **&ppNewCreatures, int newSize, std::ifstream *pNameFile, const Army *pSourceArmy);
    void deallocateCreatures(Creature **&ppCreatureList, int creatureCount);
    void battleCreatures(Creature &thisCreature, Creature &opponentCreature, const std::string &opponentArmyName, int creaturePosition);
    void attack(Creature &attacker, const std::string &attackerArmyName, Creature &defender, const std::string &defenderArmyName, int roundNumber);
    void printBattleHeader() const;
    void announceCreatureWinner(const Creature &thisCreature, const Creature &opponentCreature, const std::string &opponentArmyName, int roundCount) const;
    bool isValidArmy(const std::string &armyName, int armySize) const;
};

#endif
