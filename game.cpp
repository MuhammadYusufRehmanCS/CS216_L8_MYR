// CS 216 Lab #8 Abstract
// Muhammad Yusuf Rehman

#include "game.h"

#include "functions.h"

#include <fstream>
#include <iostream>
#include <limits>

using namespace std;

// Description: Initializes a Game object that manages one complete Army battle per request.
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
        string armyOneName = getArmyName(FIRST_ARMY_QUESTION);
        string armyTwoName = getArmyName(SECOND_ARMY_QUESTION);
        int armySize = getArmySize();
        Army armyOne(armyOneName, armySize, nameFile);
        Army armyTwo(armyTwoName, armySize, nameFile);

        if (armyOne.isGenerated() && armyTwo.isGenerated())
        {
            armyOne.print(ARMY_ONE_BEFORE_HEADING);
            armyTwo.print(ARMY_TWO_BEFORE_HEADING);
            armyOne.battle(armyTwo);
            armyOne.print(ARMY_ONE_AFTER_HEADING);
            armyTwo.print(ARMY_TWO_AFTER_HEADING);
            announceArmyWinner(armyOne, armyTwo);
        }
        else
        {
            cout << CREATURE_FILE_ERROR_MESSAGE;
        }
    }
    else
    {
        cout << INPUT_FILE_ERROR_MESSAGE;
    }
}

// Description: Compares overall remaining health and announces the winning Army.
// Precondition: All matched Creature battles are complete.
// Postcondition: Both total-health amounts and the winning Army or tie are displayed.
void Game::announceArmyWinner(const Army &armyOne, const Army &armyTwo) const
{
    const string &armyOneName = armyOne.getName();
    const string &armyTwoName = armyTwo.getName();
    int armyOneHealth = armyOne.getTotalHealth();
    int armyTwoHealth = armyTwo.getTotalHealth();

    cout << '\n' << armyOneName << " overall health: " << armyOneHealth << '\n' << armyTwoName << " overall health: " << armyTwoHealth << '\n';

    if (armyOneHealth > armyTwoHealth)
    {
        cout << armyOneName << WINNER_MESSAGE;
    }
    else if (armyTwoHealth > armyOneHealth)
    {
        cout << armyTwoName << WINNER_MESSAGE;
    }
    else
    {
        cout << TIE_MESSAGE;
    }
}
