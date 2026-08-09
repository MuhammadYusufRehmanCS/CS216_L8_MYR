// CS 216 Lab #8 Abstract
// Muhammad Yusuf Rehman

#ifndef CYBERELF_H
#define CYBERELF_H

#include "elf.h"

class Cyberelf : public Elf
{
public:
    Cyberelf();
    Cyberelf(const std::string &creatureName, int creatureStrength, int creatureHealth);

    std::string getName() const override;
    const std::string &getType() const override;
    CreatureType getTypeCode() const override;
    int getDamage() const override;
};

#endif