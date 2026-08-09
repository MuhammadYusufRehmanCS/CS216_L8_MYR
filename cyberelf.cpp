// CS 216 Lab #8 Abstract
// Muhammad Yusuf Rehman

#include "cyberelf.h"

#include <cstdlib>

using namespace std;

// Description: Initializes a Cyberelf with valid default values through the Elf constructor.
// Precondition: A Cyberelf object is being created.
// Postcondition: The Cyberelf contains a valid default Creature record.
Cyberelf::Cyberelf() : Elf(DEFAULT_CYBERELF_NAME, DEFAULT_STAT, DEFAULT_STAT)
{
}

// Description: Initializes a Cyberelf with the supplied complete Creature record through Elf.
// Precondition: The supplied values may be valid or invalid.
// Postcondition: The Elf constructor passes the complete record to the Creature constructor.
Cyberelf::Cyberelf(const string &creatureName, int creatureStrength, int creatureHealth) : Elf(creatureName, creatureStrength, creatureHealth)
{
}

// Description: Returns the Cyberelf identifier together with its class name.
// Precondition: The Cyberelf contains a valid Creature record.
// Postcondition: A descriptive Cyberelf name is returned and the object remains unchanged.
string Cyberelf::getName() const
{
    return getId() + " the " + CYBERELF_TYPE_NAME;
}

// Description: Returns the Cyberelf class name.
// Precondition: The Cyberelf object exists.
// Postcondition: A const reference to the Cyberelf type is returned and the object remains unchanged.
const string &Cyberelf::getType() const
{
    return CYBERELF_TYPE_NAME;
}

// Description: Returns the Cyberelf type code used when an Army copies a Creature list.
// Precondition: The Cyberelf object exists.
// Postcondition: The Cyberelf enumerator is returned and the object remains unchanged.
CreatureType Cyberelf::getTypeCode() const
{
    return CYBERELF;
}

// Description: Calculates Elf damage and adds bonus damage with the configured Cyberelf chance.
// Precondition: The Cyberelf contains valid strength and the random number generator has been seeded.
// Postcondition: Creature, Elf, and Cyberelf damage rules are combined and returned.
int Cyberelf::getDamage() const
{
    int damage = Elf::getDamage();

    if ((rand() % PERCENT_RANGE) < CYBERELF_ATTACK_CHANCE)
    {
        damage = damage + CYBERELF_BONUS_DAMAGE;
    }

    return damage;
}