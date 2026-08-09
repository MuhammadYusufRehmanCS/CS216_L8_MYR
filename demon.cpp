// CS 216 Lab #8 Abstract
// Muhammad Yusuf Rehman

#include "demon.h"

#include <cstdlib>

using namespace std;

// Description: Initializes a Demon with valid default values through the Creature constructor.
// Precondition: A Demon object is being created.
// Postcondition: The Demon contains a valid default Creature record.
Demon::Demon() : Creature(DEFAULT_DEMON_NAME, DEFAULT_STAT, DEFAULT_STAT)
{
}

// Description: Initializes a Demon with the supplied complete Creature record.
// Precondition: The supplied values may be valid or invalid.
// Postcondition: The Creature constructor stores the valid record or keeps valid defaults.
Demon::Demon(const string &creatureName, int creatureStrength, int creatureHealth) : Creature(creatureName, creatureStrength, creatureHealth)
{
}

// Description: Returns the Demon identifier together with its class name.
// Precondition: The Demon contains a valid Creature record.
// Postcondition: A descriptive Demon name is returned and the object remains unchanged.
string Demon::getName() const
{
    return getId() + " the " + DEMON_TYPE_NAME;
}

// Description: Returns the Demon class name.
// Precondition: The Demon object exists.
// Postcondition: A const reference to the Demon type is returned and the object remains unchanged.
const string &Demon::getType() const
{
    return DEMON_TYPE_NAME;
}

// Description: Returns the Demon type code used when an Army copies a Creature list.
// Precondition: The Demon object exists.
// Postcondition: The Demon enumerator is returned and the object remains unchanged.
CreatureType Demon::getTypeCode() const
{
    return DEMON;
}

// Description: Calculates Creature damage and adds bonus damage with the configured Demon chance.
// Precondition: The Demon contains valid strength and the random number generator has been seeded.
// Postcondition: Complete Demon damage is returned and the object remains unchanged.
int Demon::getDamage() const
{
    int damage = Creature::getDamage();

    if ((rand() % PERCENT_RANGE) < DEMON_ATTACK_CHANCE)
    {
        damage = damage + DEMON_BONUS_DAMAGE;
    }

    return damage;
}