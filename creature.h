// CS 216 Lab #8 Abstract
// Muhammad Yusuf Rehman

#ifndef CREATURE_H
#define CREATURE_H

#include "functions.h"

#include <string>

class Creature
{
// Protected so every derived Creature reads these members directly and needs no getter call.
protected:
    std::string name = DEFAULT_CREATURE_NAME;
    int strength = DEFAULT_STAT;
    int health = DEFAULT_STAT;

public:
    Creature();
    Creature(const std::string &creatureName, int creatureStrength, int creatureHealth);
    virtual ~Creature();

    void setCreature(const std::string &creatureName, int creatureStrength, int creatureHealth);
    void takeDamage(int damage);
    void reset();

    const std::string &getId() const;
    virtual std::string getName() const = 0;
    virtual const std::string &getType() const = 0;
    virtual CreatureType getTypeCode() const = 0;
    int getStrength() const;
    int getHealth() const;
    virtual int getDamage() const;
    virtual std::string to_String() const;

private:
    bool isValidCreature(const std::string &creatureName, int creatureStrength, int creatureHealth) const;
};

#endif
