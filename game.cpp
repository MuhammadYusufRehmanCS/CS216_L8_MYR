// CS 216 Lab #8 Abstract
// Muhammad Yusuf Rehman

#include "game.h"

#include "functions.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>

using namespace std;

// Description: Initializes a stateless Game object.
// Precondition: A Game object is being created.
// Postcondition: The Game object is ready to manage repeated Army battles.
Game::Game()
{
}

// Description: Gets two Army names and one shared arbitrary size, generates both Armies, and manages one complete battle.
// Precondition: Standard input is available and the Creature-name file may be opened.
// Postcondition: A complete Army battle is played when both Armies generate successfully.
void Game::playGame()
{
    ifstream nameFile(INPUT_FILE_NAME.c_str());

    if (nameFile)
    {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        string armyOneName = getArmyName("Enter the first army name: ");
        string armyTwoName = getArmyName("Enter the second army name: ");
        int armySize = getArmySize();
        Army armyOne(armyOneName, armySize);
        Army armyTwo(armyTwoName, armySize);
        bool isArmyOneGenerated = armyOne.generateCreatures(nameFile);
        bool isArmyTwoGenerated = armyTwo.generateCreatures(nameFile);

        if (isArmyOneGenerated && isArmyTwoGenerated)
        {
            armyOne.print("Army #1 Stats before the Battle");
            armyTwo.print("Army #2 Stats before the Battle");
            battleArmies(armyOne, armyTwo);
            armyOne.print("Army #1 Stats after the Battle");
            armyTwo.print("Army #2 Stats after the Battle");
            announceArmyWinner(armyOne, armyTwo);
        }
        else
        {
            cout << CREATURE_FILE_ERROR_MESSAGE << '\n';
        }
    }
    else
    {
        cout << INPUT_FILE_ERROR_MESSAGE << '\n';
    }
}

// Description: Matches Creatures at the same positions and runs every individual battle.
// Precondition: Both Armies have the same positive size and valid Creature pointer lists.
// Postcondition: Every matched pair battles until one Creature reaches zero health.
void Game::battleArmies(Army &armyOne, Army &armyTwo)
{
    for (int creatureIndex = 0; creatureIndex < armyOne.size; ++creatureIndex)
    {
        battleCreatures(*armyOne.ppCreatures[creatureIndex], armyOne.name, *armyTwo.ppCreatures[creatureIndex], armyTwo.name, creatureIndex + 1);
    }
}

// Description: Alternates attacks between two matched Creatures until one reaches zero health.
// Precondition: Both Creatures are alive and belong to the supplied Army names.
// Postcondition: One Creature has zero health and the individual winner is announced.
void Game::battleCreatures(Creature &creatureOne, const string &armyOneName, Creature &creatureTwo, const string &armyTwoName, int creaturePosition)
{
    int roundNumber = 1;
    bool isArmyOneTurn = true;

    cout << "\nPosition " << creaturePosition << " Battle\n";
    printBattleHeader();

    while (creatureOne.getHealth() > 0 && creatureTwo.getHealth() > 0)
    {
        if (isArmyOneTurn)
        {
            attack(creatureOne, armyOneName, creatureTwo, armyTwoName, roundNumber);
        }
        else
        {
            attack(creatureTwo, armyTwoName, creatureOne, armyOneName, roundNumber);
        }

        isArmyOneTurn = !isArmyOneTurn;
        ++roundNumber;
    }

    announceCreatureWinner(creatureOne, armyOneName, creatureTwo, armyTwoName, roundNumber - 1);
}

// Description: Calculates one attack, updates the defender through setCreature, and prints complete attack details.
// Precondition: The attacker and defender are alive and their Army names are valid.
// Postcondition: Defender health is reduced without becoming negative and one attack row is displayed.
void Game::attack(Creature &attacker, const string &attackerArmyName, Creature &defender, const string &defenderArmyName, int roundNumber)
{
    int damage = attacker.getDamage();
    int healthBefore = defender.getHealth();
    int healthAfter = healthBefore - damage;

    if (healthAfter < 0)
    {
        healthAfter = 0;
    }

    defender.setCreature(defender.getId(), defender.getStrength(), healthAfter);
    cout << left << setw(ROUND_WIDTH) << roundNumber << " | " << setw(ARMY_WIDTH) << attackerArmyName << " | " << setw(FIGHTER_WIDTH) << attacker.getName() << " | " << right << setw(DAMAGE_WIDTH) << damage << " | " << left << setw(ARMY_WIDTH) << defenderArmyName << " | " << setw(FIGHTER_WIDTH) << defender.getName() << " | " << right << setw(HEALTH_WIDTH) << healthBefore << " | " << setw(HEALTH_WIDTH) << defender.getHealth() << '\n';
}

// Description: Prints the column headings and divider for detailed battle output.
// Precondition: Standard output is available.
// Postcondition: One complete battle table heading and divider are displayed.
void Game::printBattleHeader() const
{
    cout << left << setw(ROUND_WIDTH) << "Round" << " | " << setw(ARMY_WIDTH) << "Atk Army" << " | " << setw(FIGHTER_WIDTH) << "Attacker" << " | " << right << setw(DAMAGE_WIDTH) << "Damage" << " | " << left << setw(ARMY_WIDTH) << "Def Army" << " | " << setw(FIGHTER_WIDTH) << "Defender" << " | " << right << setw(HEALTH_WIDTH) << "Health Before" << " | " << setw(HEALTH_WIDTH) << "Health After" << '\n';
    cout << string(BATTLE_TABLE_WIDTH, '-') << '\n';
}

// Description: Announces the winning Creature, its Army, and the number of battle rounds.
// Precondition: Exactly one of the matched Creatures has zero health.
// Postcondition: The individual battle winner is displayed and neither Creature changes.
void Game::announceCreatureWinner(const Creature &creatureOne, const string &armyOneName, const Creature &creatureTwo, const string &armyTwoName, int roundCount) const
{
    string roundWord = " rounds.";

    if (roundCount == 1)
    {
        roundWord = " round.";
    }

    if (creatureOne.getHealth() > 0)
    {
        cout << creatureOne.getName() << " of " << armyOneName << " won this position battle in " << roundCount << roundWord << '\n';
    }
    else
    {
        cout << creatureTwo.getName() << " of " << armyTwoName << " won this position battle in " << roundCount << roundWord << '\n';
    }
}

// Description: Compares overall remaining health and announces the winning Army.
// Precondition: All matched Creature battles are complete.
// Postcondition: Both total-health amounts and the winning Army or tie are displayed.
void Game::announceArmyWinner(const Army &armyOne, const Army &armyTwo) const
{
    int armyOneHealth = armyOne.getTotalHealth();
    int armyTwoHealth = armyTwo.getTotalHealth();

    cout << '\n' << armyOne.name << " overall health: " << armyOneHealth << '\n' << armyTwo.name << " overall health: " << armyTwoHealth << '\n';

    if (armyOneHealth > armyTwoHealth)
    {
        cout << armyOne.name << " is the winning army.\n";
    }
    else if (armyTwoHealth > armyOneHealth)
    {
        cout << armyTwo.name << " is the winning army.\n";
    }
    else
    {
        cout << "The armies tied.\n";
    }
}