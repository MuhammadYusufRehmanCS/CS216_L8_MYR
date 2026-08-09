// CS 216 Lab #8 Abstract
// Muhammad Yusuf Rehman

#include "army.h"

#include "balrog.h"
#include "cyberelf.h"
#include "demon.h"
#include "elf.h"

#include <iomanip>
#include <iostream>
#include <new>

using namespace std;

// Description: Initializes an empty default Army through the complete Army setter.
// Precondition: An Army object is being created.
// Postcondition: The Army has a valid default name, zero size, and no allocated Creature list.
Army::Army()
{
    Creature **ppNewCreatures = nullptr;
    setArmy(DEFAULT_ARMY_NAME, 0, ppNewCreatures);
}

// Description: Initializes an Army as a deep copy of another Army.
// Precondition: rhsArmy contains a valid Army object.
// Postcondition: A complete independent copy is created or construction fails without leaking owned memory.
Army::Army(const Army &rhsArmy)
{
    Creature **ppNewCreatures = nullptr;
    bool isCreated = createCreatureArray(ppNewCreatures, rhsArmy.size, nullptr, &rhsArmy);

    if (isCreated)
    {
        setArmy(rhsArmy.name, rhsArmy.size, ppNewCreatures);
    }
}

// Description: Initializes an Army name and arbitrary size without creating individual Creatures.
// Precondition: The proposed name and size may be valid or invalid.
// Postcondition: Valid Army metadata is stored through setArmy and no Creature list is allocated yet.
Army::Army(const string &armyName, int armySize)
{
    Creature **ppNewCreatures = nullptr;
    setArmy(armyName, armySize, ppNewCreatures);
}

// Description: Releases every dynamically allocated Creature and the pointer list owned by the Army.
// Precondition: The Army may own a dynamically allocated pointer list and Creature objects.
// Postcondition: All owned memory is released and Army members are reset to safe values.
Army::~Army()
{
    deallocateCreatures(ppCreatures, size);
    name.clear();
    size = 0;
}

// Description: Replaces this Army with a deep copy of another Army.
// Precondition: rhsArmy contains a valid Army object.
// Postcondition: The complete copy replaces the old Army or the old Army remains unchanged if copying fails.
Army &Army::operator=(const Army &rhsArmy)
{
    if (this != &rhsArmy)
    {
        Creature **ppNewCreatures = nullptr;
        bool isCreated = createCreatureArray(ppNewCreatures, rhsArmy.size, nullptr, &rhsArmy);

        if (isCreated)
        {
            setArmy(rhsArmy.name, rhsArmy.size, ppNewCreatures);
        }
    }

    return *this;
}

// Description: Dynamically generates a complete replacement list containing various derived Creature objects.
// Precondition: The Army has a positive arbitrary size and nameFile is open with enough valid unique names.
// Postcondition: A complete new Creature list replaces the old list or the old Army remains unchanged.
bool Army::generateCreatures(ifstream &nameFile)
{
    Creature **ppNewCreatures = nullptr;
    bool isGenerated = createCreatureArray(ppNewCreatures, size, &nameFile, nullptr);

    if (isGenerated)
    {
        setArmy(name, size, ppNewCreatures);
    }

    return isGenerated;
}

// Description: Calculates the sum of the current health of all Creatures in the Army.
// Precondition: The Army has a valid pointer list or has not generated its Creatures yet.
// Postcondition: Overall Army health is returned and the Army remains unchanged.
int Army::getTotalHealth() const
{
    int totalHealth = 0;

    if (ppCreatures != nullptr)
    {
        for (int creatureIndex = 0; creatureIndex < size; ++creatureIndex)
        {
            totalHealth = totalHealth + ppCreatures[creatureIndex]->getHealth();
        }
    }

    return totalHealth;
}

// Description: Prints one Army heading and every generated Creature in a formatted table.
// Precondition: The Army contains a valid pointer list or has not generated its Creatures yet.
// Postcondition: Army statistics are displayed and the Army remains unchanged.
void Army::print(const string &heading) const
{
    cout << '\n' << heading << '\n' << "Army: " << name << '\n';
    cout << left << setw(CREATURE_WIDTH) << "Creature" << " | " << setw(TYPE_WIDTH) << "Type" << " | " << right << setw(NUMBER_WIDTH) << "Strength" << " | " << setw(NUMBER_WIDTH) << "Health" << '\n';
    cout << string(CREATURE_TABLE_WIDTH, '-') << '\n';

    if (ppCreatures != nullptr)
    {
        for (int creatureIndex = 0; creatureIndex < size; ++creatureIndex)
        {
            cout << ppCreatures[creatureIndex]->to_String() << '\n';
        }
    }
}

// Description: Stores all Army members as one transaction and takes ownership of a completed Creature list.
// Precondition: The proposed name and size are supplied and ppNewCreatures is nullptr or a complete list for that size.
// Postcondition: All new Army members replace the old state together or the old Army remains unchanged.
void Army::setArmy(const string &armyName, int armySize, Creature **&ppNewCreatures)
{
    bool isValid = isValidArmy(armyName, armySize);

    if (isValid)
    {
        try
        {
            string proposedName = armyName;
            name = proposedName;
            deallocateCreatures(ppCreatures, size);
            ppCreatures = ppNewCreatures;
            ppNewCreatures = nullptr;
            size = armySize;
        }
        catch (const bad_alloc &)
        {
            deallocateCreatures(ppNewCreatures, armySize);
            throw;
        }
    }
    else
    {
        deallocateCreatures(ppNewCreatures, armySize);
        cout << INVALID_ARMY_MESSAGE << '\n';
    }
}

// Description: Allocates one pointer list and every derived Creature needed for generation or deep copying.
// Precondition: newSize is nonnegative and either a name file, a source Army, or neither for an empty Army is supplied.
// Postcondition: A complete independent Creature list is returned through ppNewCreatures or all partial DMA is released.
bool Army::createCreatureArray(Creature **&ppNewCreatures, int newSize, ifstream *pNameFile, const Army *pSourceArmy)
{
    bool isCreated = newSize >= 0;
    bool isAllocationNeeded = newSize > 0;

    if (isCreated && newSize > 0)
    {
        isCreated = (pNameFile != nullptr && pSourceArmy == nullptr) || (pNameFile == nullptr && pSourceArmy != nullptr);
    }

    if (isCreated && pSourceArmy != nullptr && pSourceArmy->ppCreatures == nullptr)
    {
        isAllocationNeeded = false;
    }

    if (isCreated && isAllocationNeeded)
    {
        try
        {
            ppNewCreatures = new Creature *[newSize]();

            for (int creatureIndex = 0; creatureIndex < newSize && isCreated; ++creatureIndex)
            {
                string creatureName = DEFAULT_CREATURE_NAME;
                int creatureStrength = DEFAULT_STAT;
                int creatureHealth = DEFAULT_STAT;
                CreatureType creatureType = DEMON;

                if (pSourceArmy != nullptr)
                {
                    creatureName = pSourceArmy->ppCreatures[creatureIndex]->getId();
                    creatureStrength = pSourceArmy->ppCreatures[creatureIndex]->getStrength();
                    creatureHealth = pSourceArmy->ppCreatures[creatureIndex]->getHealth();
                    const string &sourceType = pSourceArmy->ppCreatures[creatureIndex]->getType();

                    if (sourceType == DEMON_TYPE_NAME)
                    {
                        creatureType = DEMON;
                    }
                    else if (sourceType == BALROG_TYPE_NAME)
                    {
                        creatureType = BALROG;
                    }
                    else if (sourceType == ELF_TYPE_NAME)
                    {
                        creatureType = ELF;
                    }
                    else if (sourceType == CYBERELF_TYPE_NAME)
                    {
                        creatureType = CYBERELF;
                    }
                    else
                    {
                        isCreated = false;
                    }
                }
                else if (pNameFile != nullptr)
                {
                    getline(*pNameFile, creatureName);
                    isCreated = static_cast<bool>(*pNameFile) && isValidArmyName(creatureName);

                    if (isCreated)
                    {
                        creatureStrength = randomNumber(MIN_ARMY_STAT, MAX_ARMY_STAT);
                        creatureHealth = randomNumber(MIN_ARMY_STAT, MAX_ARMY_STAT);
                        creatureType = static_cast<CreatureType>(randomNumber(DEMON, CREATURE_TYPE_COUNT - 1));
                    }
                }
                else
                {
                    isCreated = false;
                }

                if (isCreated)
                {
                    switch (creatureType)
                    {
                        case DEMON:
                            ppNewCreatures[creatureIndex] = new Demon(creatureName, creatureStrength, creatureHealth);
                            break;

                        case BALROG:
                            ppNewCreatures[creatureIndex] = new Balrog(creatureName, creatureStrength, creatureHealth);
                            break;

                        case ELF:
                            ppNewCreatures[creatureIndex] = new Elf(creatureName, creatureStrength, creatureHealth);
                            break;

                        case CYBERELF:
                            ppNewCreatures[creatureIndex] = new Cyberelf(creatureName, creatureStrength, creatureHealth);
                            break;

                        default:
                            isCreated = false;
                    }
                }
            }
        }
        catch (const bad_alloc &)
        {
            deallocateCreatures(ppNewCreatures, newSize);
            throw;
        }
    }

    if (!isCreated)
    {
        deallocateCreatures(ppNewCreatures, newSize);
    }

    return isCreated;
}

// Description: Deletes every existing dynamically allocated Creature and then deletes the pointer list.
// Precondition: ppCreatureList is nullptr or points to a dynamically allocated pointer list.
// Postcondition: Every owned object and the pointer list are deleted and the pointer is nullptr.
void Army::deallocateCreatures(Creature **&ppCreatureList, int creatureCount)
{
    if (ppCreatureList != nullptr)
    {
        for (int creatureIndex = 0; creatureIndex < creatureCount; ++creatureIndex)
        {
            if (ppCreatureList[creatureIndex] != nullptr)
            {
                delete ppCreatureList[creatureIndex];
                ppCreatureList[creatureIndex] = nullptr;
            }
        }

        delete [] ppCreatureList;
        ppCreatureList = nullptr;
    }
}

// Description: Determines whether a proposed Army name and size form a valid Army record.
// Precondition: A proposed Army name and size are supplied.
// Postcondition: True is returned only when the Army name is nonblank and size is nonnegative.
bool Army::isValidArmy(const string &armyName, int armySize) const
{
    bool isValid = isValidArmyName(armyName) && armySize >= 0;

    return isValid;
}