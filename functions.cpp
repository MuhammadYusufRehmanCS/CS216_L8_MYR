// CS 216 Lab #8 Abstract
// Muhammad Yusuf Rehman

#include "functions.h"

#include <cctype>
#include <cstdlib>
#include <iostream>
#include <limits>

using namespace std;

extern const string LAB_NAME = "CS 216 Lab #8 Abstract";
extern const string STUDENT_NAME = "Muhammad Yusuf Rehman";
extern const string INPUT_FILE_NAME = "in_names.txt";

extern const string DEFAULT_CREATURE_NAME = "DefaultCreature";
extern const string DEFAULT_DEMON_NAME = "DefaultDemon";
extern const string DEFAULT_BALROG_NAME = "DefaultBalrog";
extern const string DEFAULT_ELF_NAME = "DefaultElf";
extern const string DEFAULT_CYBERELF_NAME = "DefaultCyberelf";
extern const string DEFAULT_ARMY_NAME = "DefaultArmy";
extern const string INVALID_NAME = "InvalidName";

extern const string DEMON_TYPE_NAME = "Demon";
extern const string BALROG_TYPE_NAME = "Balrog";
extern const string ELF_TYPE_NAME = "Elf";
extern const string CYBERELF_TYPE_NAME = "Cyberelf";

extern const string MENU_TEXT = "\n\nMenu:\n"
                                "1. Battle\n"
                                "2. Quit\n"
                                "Enter your choice: ";
extern const string FIRST_ARMY_QUESTION = "Enter the first army name: ";
extern const string SECOND_ARMY_QUESTION = "Enter the second army name: ";
extern const string ARMY_SIZE_QUESTION = "Enter the number of creatures in each army: ";

extern const string ARMY_ONE_BEFORE_HEADING = "Army #1 Stats before the Battle";
extern const string ARMY_TWO_BEFORE_HEADING = "Army #2 Stats before the Battle";
extern const string ARMY_ONE_AFTER_HEADING = "Army #1 Stats after the Battle";
extern const string ARMY_TWO_AFTER_HEADING = "Army #2 Stats after the Battle";

extern const string INVALID_MENU_MESSAGE = "Invalid menu choice. Select from the menu above.\n";
extern const string INVALID_NAME_MESSAGE = "Enter a nonblank name.\n";
extern const string INVALID_SIZE_MESSAGE = "Enter a positive whole number.\n";
extern const string INVALID_ARMY_MESSAGE = "Invalid army data. The army remains unchanged.\n";
extern const string INVALID_CREATURE_MESSAGE = "Invalid creature data. The creature remains unchanged.\n";
extern const string INPUT_FILE_ERROR_MESSAGE = "The creature-name input file could not be opened.\n";
extern const string CREATURE_FILE_ERROR_MESSAGE = "The army could not be generated from the creature-name file.\n";
extern const string MEMORY_ERROR_MESSAGE = "Dynamic memory allocation failed. The army was not generated.\n";
extern const string PROGRAM_ERROR_MESSAGE = "Dynamic memory allocation failed. The program ended safely.\n";
extern const string BATTLE_ERROR_MESSAGE = "Both armies must be generated and the same size to battle.\n";
extern const string QUIT_MESSAGE = "Program ended.\n";
extern const string TIE_MESSAGE = "The armies tied.\n";

extern const int INVALID_STAT = -1;
extern const int DEFAULT_STAT = 45;
extern const int MIN_HEALTH = 0;
extern const int MIN_VALID_STRENGTH = 1;
extern const int MIN_RESET_STAT = 30;
extern const int MAX_RESET_STAT = 150;
extern const int MIN_ARMY_STAT = 45;
extern const int MAX_ARMY_STAT = 275;
extern const int MIN_ARMY_SIZE = 1;

// Attack chances are constants so they can be changed in one place.
// These percentages continue the written Creature rules from Lab #7.
extern const int DEMON_ATTACK_CHANCE = 15;
extern const int ELF_ATTACK_CHANCE = 20;
extern const int CYBERELF_ATTACK_CHANCE = 30;
extern const int DEMON_BONUS_DAMAGE = 40;
extern const int CYBERELF_BONUS_DAMAGE = 50;
extern const int ELF_DAMAGE_MULTIPLIER = 2;
extern const int PERCENT_RANGE = 100;

extern const int CREATURE_WIDTH = 18;
extern const int TYPE_WIDTH = 14;
extern const int NUMBER_WIDTH = 12;
extern const int ROUND_WIDTH = 8;
extern const int ARMY_WIDTH = 16;
extern const int FIGHTER_WIDTH = 28;
extern const int DAMAGE_WIDTH = 10;
extern const int HEALTH_WIDTH = 14;
extern const int SEPARATOR_WIDTH = 3;
extern const int CREATURE_TABLE_WIDTH = CREATURE_WIDTH + TYPE_WIDTH + NUMBER_WIDTH + NUMBER_WIDTH + (SEPARATOR_WIDTH * 3);
extern const int BATTLE_TABLE_WIDTH = ROUND_WIDTH + ARMY_WIDTH + FIGHTER_WIDTH + DAMAGE_WIDTH + ARMY_WIDTH + FIGHTER_WIDTH + HEALTH_WIDTH + HEALTH_WIDTH + (SEPARATOR_WIDTH * 7);

// Description: Displays the two required menu choices and the input prompt.
// Precondition: Standard output is available.
// Postcondition: The menu is displayed and the program is ready for input.
void displayMenu()
{
    cout << MENU_TEXT;
}

// Description: Clears failed or unwanted standard input and displays a reusable error message.
// Precondition: The input stream may be failed or contain unwanted characters.
// Postcondition: The input stream is ready for another input operation.
void clearCin(const string &errorMessage)
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << errorMessage;
}

// Description: Gets one valid Army name from the user.
// Precondition: The question contains the prompt to display and standard input is available.
// Postcondition: A nonblank Army name is returned even when the input stream ends.
string getArmyName(const string &question)
{
    string armyName = DEFAULT_ARMY_NAME;
    bool isValid = false;

    do
    {
        cout << question;
        getline(cin, armyName);
        isValid = isValidName(armyName);

        if (!isValid)
        {
            armyName = DEFAULT_ARMY_NAME;
            cout << INVALID_NAME_MESSAGE;
        }
    } while (!isValid && !cin.eof());

    return armyName;
}

// Description: Gets one positive shared Army size from the user.
// Precondition: Standard input is available.
// Postcondition: A whole number no smaller than one is returned even when the input stream ends.
int getArmySize()
{
    int armySize = MIN_ARMY_SIZE;
    bool isValid = false;

    do
    {
        cout << ARMY_SIZE_QUESTION;
        cin >> armySize;
        isValid = !cin.fail() && armySize >= MIN_ARMY_SIZE;

        if (!isValid)
        {
            armySize = MIN_ARMY_SIZE;
            clearCin(INVALID_SIZE_MESSAGE);
        }
    } while (!isValid && !cin.eof());

    return armySize;
}

// Description: Determines whether a proposed Army or Creature name contains at least one nonspace character.
// Precondition: A proposed name is supplied.
// Postcondition: True is returned only when the name is not blank.
bool isValidName(const string &proposedName)
{
    bool isValid = false;

    for (int characterIndex = 0; characterIndex < static_cast<int>(proposedName.length()) && !isValid; ++characterIndex)
    {
        unsigned char character = static_cast<unsigned char>(proposedName[characterIndex]);
        isValid = isspace(character) == 0;
    }

    return isValid;
}

// Description: Generates one random integer inside an inclusive range.
// Precondition: minimum is less than or equal to maximum and the random number generator is seeded.
// Postcondition: One random integer from minimum through maximum is returned.
int randomNumber(int minimum, int maximum)
{
    int randomValue = rand() % (maximum - minimum + 1) + minimum;

    return randomValue;
}
