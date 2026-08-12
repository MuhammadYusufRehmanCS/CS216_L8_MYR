// CS 216 Lab #8 Abstract
// Muhammad Yusuf Rehman

#include "balrog.h"

using namespace std;

// Description: Initializes a Balrog with valid default values through the Creature constructor.
// Precondition: A Balrog object is being created.
// Postcondition: The Balrog contains a valid default Creature record.
Balrog::Balrog() : Creature(DEFAULT_BALROG_NAME, DEFAULT_STAT, DEFAULT_STAT)
{
}

// Description: Initializes a Balrog with the supplied complete Creature record.
// Precondition: The supplied values may be valid or invalid.
// Postcondition: The Creature constructor stores the valid record or keeps valid defaults.
Balrog::Balrog(const string &creatureName, int creatureStrength, int creatureHealth) : Creature(creatureName, creatureStrength, creatureHealth)
{
}

// Description: Returns the Balrog identifier together with its class name.
// Precondition: The Balrog contains a valid Creature record.
// Postcondition: A descriptive Balrog name is returned and the object remains unchanged.
string Balrog::getName() const
{
    return name + " the " + BALROG_TYPE_NAME;
}

// Description: Returns the Balrog class name.
// Precondition: The Balrog object exists.
// Postcondition: A const reference to the Balrog type is returned and the object remains unchanged.
const string &Balrog::getType() const
{
    return BALROG_TYPE_NAME;
}

// Description: Returns the Balrog type code used when an Army copies a Creature list.
// Precondition: The Balrog object exists.
// Postcondition: The Balrog enumerator is returned and the object remains unchanged.
CreatureType Balrog::getTypeCode() const
{
    return BALROG;
}

// Description: Calculates two independent basic Creature attacks for the Balrog.
// Precondition: The Balrog contains valid strength and the random number generator has been seeded.
// Postcondition: The sum of two Creature attacks is returned and the Balrog remains unchanged.
int Balrog::getDamage() const
{
    int damage = Creature::getDamage() + Creature::getDamage();

    return damage;
}