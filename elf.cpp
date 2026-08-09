// CS 216 Lab #8 Abstract
// Muhammad Yusuf Rehman

#include "elf.h"

#include <cstdlib>

using namespace std;

// Description: Initializes an Elf with valid default values through the Creature constructor.
// Precondition: An Elf object is being created.
// Postcondition: The Elf contains a valid default Creature record.
Elf::Elf() : Creature(DEFAULT_ELF_NAME, DEFAULT_STAT, DEFAULT_STAT)
{
}

// Description: Initializes an Elf with the supplied complete Creature record.
// Precondition: The supplied values may be valid or invalid.
// Postcondition: The Creature constructor stores the valid record or keeps valid defaults.
Elf::Elf(const string &creatureName, int creatureStrength, int creatureHealth) : Creature(creatureName, creatureStrength, creatureHealth)
{
}

// Description: Returns the Elf identifier together with its class name.
// Precondition: The Elf contains a valid Creature record.
// Postcondition: A descriptive Elf name is returned and the object remains unchanged.
string Elf::getName() const
{
    return getId() + " the " + ELF_TYPE_NAME;
}

// Description: Returns the Elf class name.
// Precondition: The Elf object exists.
// Postcondition: A const reference to the Elf type is returned and the object remains unchanged.
const string &Elf::getType() const
{
    return ELF_TYPE_NAME;
}

// Description: Calculates Creature damage and doubles it with the configured Elf chance.
// Precondition: The Elf contains valid strength and the random number generator has been seeded.
// Postcondition: Complete Elf damage is returned and the object remains unchanged.
int Elf::getDamage() const
{
    int damage = Creature::getDamage();

    if ((rand() % PERCENT_RANGE) < ELF_ATTACK_CHANCE)
    {
        damage = damage * 2;
    }

    return damage;
}