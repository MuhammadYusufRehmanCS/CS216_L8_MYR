// CS 216 Lab #8 Abstract
// Muhammad Yusuf Rehman

#ifndef BALROG_H
#define BALROG_H

#include "creature.h"

class Balrog : public Creature
{
public:
    Balrog();
    Balrog(const std::string &creatureName, int creatureStrength, int creatureHealth);

    std::string getName() const override;
    const std::string &getType() const override;
    CreatureType getTypeCode() const override;
    int getDamage() const override;
};

#endif