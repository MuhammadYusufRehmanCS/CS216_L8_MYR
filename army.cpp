// CS 216 Lab #8 Abstract
// Muhammad Yusuf Rehman

#include "army.h"

#include "balrog.h"
#include "cyberelf.h"
#include "demon.h"
#include "elf.h"

#include <iomanip>
#include <iostream>

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
// Postcondition: A complete independent copy is created or the valid default Army remains.
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

// Description: Initializes an Army and dynamically generates its complete list of various Creatures.
// Precondition: nameFile is open and holds enough valid unique names for armySize Creatures.
// Postcondition: A complete Creature list is generated or the Army stays valid with no Creature list.
Army::Army(const string &armyName, int armySize, ifstream &nameFile)
{
    Creature **ppNewCreatures = nullptr;
    setArmy(armyName, armySize, ppNewCreatures);
    generateCreatures(nameFile);
}

// Description: Releases every dynamically allocated Creature and resets all Army members to invalid values.
// Precondition: The Army may own a dynamically allocated pointer list and Creature objects.
// Postcondition: All owned memory is released and no Army data is left behind.
Army::~Army()
{
    deallocateCreatures(ppCreatures, size);
    name = INVALID_NAME;
    size = INVALID_STAT;
}

// Description: Replaces this Army with a deep copy of another Army.
// Precondition: rhsArmy contains a valid Army object.
// Postcondition: The complete copy replaces the old Army or the old Army remains unchanged.
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

// Description: Reports whether this Army currently owns a generated list of Creatures.
// Precondition: The Army object exists.
// Postcondition: True is returned only when a Creature list is allocated and the Army remains unchanged.
bool Army::isGenerated() const
{
    bool isReady = ppCreatures != nullptr;

    return isReady;
}

// Description: Returns the Army name without copying the string.
// Precondition: The Army object contains a valid record.
// Postcondition: A const reference to the Army name is returned and the Army remains unchanged.
const string &Army::getName() const
{
    return name;
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

// Description: Battles this Army against an opposing Army one matched position at a time.
// Precondition: Both Armies have generated Creature lists of the same size.
// Postcondition: Every matched pair battles until one Creature reaches zero health.
void Army::battle(Army &opponentArmy)
{
    bool isReady = ppCreatures != nullptr && opponentArmy.ppCreatures != nullptr && size == opponentArmy.size;

    if (isReady)
    {
        for (int creatureIndex = 0; creatureIndex < size; ++creatureIndex)
        {
            battleCreatures(*ppCreatures[creatureIndex], *opponentArmy.ppCreatures[creatureIndex], opponentArmy.name, creatureIndex + 1);
        }
    }
    else
    {
        cout << BATTLE_ERROR_MESSAGE;
    }
}

// Description: Prints one Army heading and every generated Creature in a formatted table.
// Precondition: The Army contains a valid pointer list or has not generated its Creatures yet.
// Postcondition: Army statistics are displayed and the Army remains unchanged.
void Army::print(const string &heading) const
{
    cout << '\n' << heading << "\nArmy: " << name << '\n'
         << left << setw(CREATURE_WIDTH) << "Creature" << " | " << setw(TYPE_WIDTH) << "Type" << " | " << right << setw(NUMBER_WIDTH) << "Strength" << " | " << setw(NUMBER_WIDTH) << "Health" << '\n'
         << string(CREATURE_TABLE_WIDTH, '-') << '\n';

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
        string proposedName = armyName;
        name = proposedName;
        deallocateCreatures(ppCreatures, size);
        ppCreatures = ppNewCreatures;
        ppNewCreatures = nullptr;
        size = armySize;
    }
    else
    {
        deallocateCreatures(ppNewCreatures, armySize);
        cout << INVALID_ARMY_MESSAGE;
    }
}

// Description: Dynamically generates a complete replacement list containing various derived Creature objects.
// Precondition: The Army has a positive arbitrary size and nameFile is open with enough valid unique names.
// Postcondition: A complete new Creature list replaces the old list or the old Army remains unchanged.
void Army::generateCreatures(ifstream &nameFile)
{
    Creature **ppNewCreatures = nullptr;
    bool isGeneratedNow = createCreatureArray(ppNewCreatures, size, &nameFile, nullptr);

    if (isGeneratedNow)
    {
        setArmy(name, size, ppNewCreatures);
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
        // The Army allocates and cleans up its own memory here so that a failed
        // allocation never leaves a partly built list behind for a caller to repair.
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
                    creatureType = pSourceArmy->ppCreatures[creatureIndex]->getTypeCode();
                }
                else
                {
                    getline(*pNameFile, creatureName);
                    isCreated = static_cast<bool>(*pNameFile) && isValidName(creatureName);

                    if (isCreated)
                    {
                        creatureStrength = randomNumber(MIN_ARMY_STAT, MAX_ARMY_STAT);
                        creatureHealth = randomNumber(MIN_ARMY_STAT, MAX_ARMY_STAT);
                        creatureType = static_cast<CreatureType>(randomNumber(DEMON, CREATURE_TYPE_COUNT - 1));
                    }
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
            isCreated = false;
            cout << MEMORY_ERROR_MESSAGE;
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

// Description: Alternates attacks between two matched Creatures until one reaches zero health.
// Precondition: Both Creatures are alive and opponentArmyName names the opposing Army.
// Postcondition: One Creature has zero health and the individual winner is announced.
void Army::battleCreatures(Creature &thisCreature, Creature &opponentCreature, const string &opponentArmyName, int creaturePosition)
{
    int roundNumber = 1;
    bool isThisArmyTurn = true;

    cout << "\nPosition " << creaturePosition << " Battle\n";
    printBattleHeader();

    while (thisCreature.getHealth() > MIN_HEALTH && opponentCreature.getHealth() > MIN_HEALTH)
    {
        if (isThisArmyTurn)
        {
            attack(thisCreature, name, opponentCreature, opponentArmyName, roundNumber);
        }
        else
        {
            attack(opponentCreature, opponentArmyName, thisCreature, name, roundNumber);
        }

        isThisArmyTurn = !isThisArmyTurn;
        ++roundNumber;
    }

    announceCreatureWinner(thisCreature, opponentCreature, opponentArmyName, roundNumber - 1);
}

// Description: Calculates one attack, lets the defender apply the damage to itself, and prints the attack details.
// Precondition: The attacker and defender are alive and their Army names are valid.
// Postcondition: Defender health is reduced without becoming negative and one attack row is displayed.
void Army::attack(Creature &attacker, const string &attackerArmyName, Creature &defender, const string &defenderArmyName, int roundNumber)
{
    int damage = attacker.getDamage();
    int healthBefore = defender.getHealth();

    defender.takeDamage(damage);
    cout << left << setw(ROUND_WIDTH) << roundNumber << " | " << setw(ARMY_WIDTH) << attackerArmyName << " | " << setw(FIGHTER_WIDTH) << attacker.getName() << " | " << right << setw(DAMAGE_WIDTH) << damage << " | " << left << setw(ARMY_WIDTH) << defenderArmyName << " | " << setw(FIGHTER_WIDTH) << defender.getName() << " | " << right << setw(HEALTH_WIDTH) << healthBefore << " | " << setw(HEALTH_WIDTH) << defender.getHealth() << '\n';
}

// Description: Prints the column headings and divider for detailed battle output.
// Precondition: Standard output is available.
// Postcondition: One complete battle table heading and divider are displayed.
void Army::printBattleHeader() const
{
    cout << left << setw(ROUND_WIDTH) << "Round" << " | " << setw(ARMY_WIDTH) << "Atk Army" << " | " << setw(FIGHTER_WIDTH) << "Attacker" << " | " << right << setw(DAMAGE_WIDTH) << "Damage" << " | " << left << setw(ARMY_WIDTH) << "Def Army" << " | " << setw(FIGHTER_WIDTH) << "Defender" << " | " << right << setw(HEALTH_WIDTH) << "Health Before" << " | " << setw(HEALTH_WIDTH) << "Health After" << '\n'
         << string(BATTLE_TABLE_WIDTH, '-') << '\n';
}

// Description: Announces the winning Creature, its Army, and the number of battle rounds.
// Precondition: Exactly one of the matched Creatures has zero health.
// Postcondition: The individual battle winner is displayed and neither Creature changes.
void Army::announceCreatureWinner(const Creature &thisCreature, const Creature &opponentCreature, const string &opponentArmyName, int roundCount) const
{
    const Creature *pWinner = &opponentCreature;
    const string *pWinnerArmyName = &opponentArmyName;
    string roundWord = ROUNDS_WORD;

    if (roundCount == 1)
    {
        roundWord = ROUND_WORD;
    }

    if (thisCreature.getHealth() > MIN_HEALTH)
    {
        pWinner = &thisCreature;
        pWinnerArmyName = &name;
    }

    cout << pWinner->getName() << " of " << *pWinnerArmyName << POSITION_WINNER_MESSAGE << roundCount << roundWord;
}

// Description: Determines whether a proposed Army name and size form a valid Army record.
// Precondition: A proposed Army name and size are supplied.
// Postcondition: True is returned only when the Army name is nonblank and size is nonnegative.
bool Army::isValidArmy(const string &armyName, int armySize) const
{
    bool isValid = isValidName(armyName) && armySize >= 0;

    return isValid;
}
