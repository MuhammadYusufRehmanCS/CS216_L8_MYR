// CS 216 Lab #8 Abstract
// Muhammad Yusuf Rehman

#ifndef DEMON_H
#define DEMON_H

#include "creature.h"

class Demon : public Creature
{
public:
    Demon();
    Demon(const std::string &creatureName, int creatureStrength, int creatureHealth);

    std::string getName() const override;
    const std::string &getType() const override;
    CreatureType getTypeCode() const override;
    int getDamage() const override;
};

#endif