// CS 216 Lab #8 Abstract
// Muhammad Yusuf Rehman

#include "creature.h"

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

// Description: Initializes the abstract Creature base with valid default member values through setCreature.
// Precondition: A derived Creature object is being created.
// Postcondition: All Creature member variables contain valid default values.
Creature::Creature()
{
    setCreature(DEFAULT_CREATURE_NAME, DEFAULT_STAT, DEFAULT_STAT);
}

// Description: Initializes the abstract Creature base with one complete supplied record through setCreature.
// Precondition: A derived Creature object is being created and the supplied values may be valid or invalid.
// Postcondition: A valid record is stored or the initialized defaults remain unchanged.
Creature::Creature(const string &creatureName, int creatureStrength, int creatureHealth)
{
    setCreature(creatureName, creatureStrength, creatureHealth);
}

// Description: Resets every Creature member variable to an invalid value before destruction.
// Precondition: A Creature base subobject has reached the end of its lifetime.
// Postcondition: The Creature members contain invalid values and derived objects are destroyed safely through a virtual destructor.
Creature::~Creature()
{
    name.clear();
    strength = INVALID_STAT;
    health = INVALID_STAT;
}

// Description: Validates and stores all Creature member variables as one complete transaction.
// Precondition: The Creature already contains valid initialized member values.
// Postcondition: All supplied values are stored together or the previous record remains unchanged.
void Creature::setCreature(const string &creatureName, int creatureStrength, int creatureHealth)
{
    bool isInputValid = isValidCreature(creatureName, creatureStrength, creatureHealth);

    if (isInputValid)
    {
        string proposedName = creatureName;
        name = proposedName;
        strength = creatureStrength;
        health = creatureHealth;
    }
    else
    {
        cout << INVALID_CREATURE_MESSAGE << '\n';
    }
}

// Description: Resets Creature strength and health to random values from 30 through 150.
// Precondition: The random number generator has been seeded and the Creature record is valid.
// Postcondition: The Creature keeps its name and receives a complete new valid statistic record.
void Creature::reset()
{
    int proposedStrength = randomNumber(MIN_RESET_STAT, MAX_RESET_STAT);
    int proposedHealth = randomNumber(MIN_RESET_STAT, MAX_RESET_STAT);
    setCreature(name, proposedStrength, proposedHealth);
}

// Description: Returns the Creature identifier without copying the string.
// Precondition: The Creature object contains a valid record.
// Postcondition: A const reference to the identifier is returned and the Creature remains unchanged.
const string &Creature::getId() const
{
    return name;
}

// Description: Returns Creature strength.
// Precondition: The Creature object contains a valid record.
// Postcondition: Strength is returned and the Creature remains unchanged.
int Creature::getStrength() const
{
    return strength;
}

// Description: Returns Creature health.
// Precondition: The Creature object contains a valid record.
// Postcondition: Health is returned and the Creature remains unchanged.
int Creature::getHealth() const
{
    return health;
}

// Description: Calculates the basic random damage available to every derived Creature.
// Precondition: Strength is greater than zero and the random number generator has been seeded.
// Postcondition: Random damage from one through strength is returned and the Creature remains unchanged.
int Creature::getDamage() const
{
    int damage = (rand() % strength) + 1;

    return damage;
}

// Description: Formats the Creature identifier, dynamic type, strength, and health as one table row.
// Precondition: The Creature object contains a valid record and a derived getType function is available.
// Postcondition: A formatted string is returned and the Creature remains unchanged.
string Creature::to_String() const
{
    stringstream output;
    output << left << setw(CREATURE_WIDTH) << name << " | " << setw(TYPE_WIDTH) << getType() << " | " << right << setw(NUMBER_WIDTH) << strength << " | " << setw(NUMBER_WIDTH) << health;

    return output.str();
}

// Description: Checks whether all required Creature fields form one valid record.
// Precondition: A proposed name, strength, and health are supplied.
// Postcondition: True is returned only when the complete record is valid.
bool Creature::isValidCreature(const string &creatureName, int creatureStrength, int creatureHealth) const
{
    bool isValid = !creatureName.empty() && creatureStrength >= MIN_RESET_STAT && creatureStrength <= MAX_ARMY_STAT && creatureHealth >= 0 && creatureHealth <= MAX_ARMY_STAT;

    return isValid;
}