// CS 216 Lab #8 Abstract
// Muhammad Yusuf Rehman

#ifndef ARMY_H
#define ARMY_H

#include "creature.h"

#include <fstream>
#include <string>

class Game;

class Army
{
private:
    std::string name = DEFAULT_ARMY_NAME;
    int size = 0;
    Creature **ppCreatures = nullptr;

    friend class Game;

public:
    Army();
    Army(const Army &rhsArmy);
    Army(const std::string &armyName, int armySize);
    ~Army();

    Army &operator=(const Army &rhsArmy);

    bool generateCreatures(std::ifstream &nameFile);

    int getTotalHealth() const;
    void print(const std::string &heading) const;

private:
    void setArmy(const std::string &armyName, int armySize, Creature **&ppNewCreatures);
    bool createCreatureArray(Creature **&ppNewCreatures, int newSize, std::ifstream *pNameFile, const Army *pSourceArmy);
    void deallocateCreatures(Creature **&ppCreatureList, int creatureCount);
    bool isValidArmy(const std::string &armyName, int armySize) const;
};

#endif