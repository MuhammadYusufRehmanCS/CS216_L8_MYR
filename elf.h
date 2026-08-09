// CS 216 Lab #8 Abstract
// Muhammad Yusuf Rehman

#ifndef ELF_H
#define ELF_H

#include "creature.h"

class Elf : public Creature
{
public:
    Elf();
    Elf(const std::string &creatureName, int creatureStrength, int creatureHealth);

    std::string getName() const override;
    const std::string &getType() const override;
    int getDamage() const override;
};

#endif