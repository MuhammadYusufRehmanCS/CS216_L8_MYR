// CS 216 Lab #8 Abstract
// Muhammad Yusuf Rehman

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>

enum MenuChoice
{
    BATTLE = 1,
    QUIT
};

enum CreatureType
{
    DEMON,
    BALROG,
    ELF,
    CYBERELF,
    CREATURE_TYPE_COUNT
};

extern const std::string LAB_NAME;
extern const std::string STUDENT_NAME;
extern const std::string INPUT_FILE_NAME;

extern const std::string DEFAULT_CREATURE_NAME;
extern const std::string DEFAULT_DEMON_NAME;
extern const std::string DEFAULT_BALROG_NAME;
extern const std::string DEFAULT_ELF_NAME;
extern const std::string DEFAULT_CYBERELF_NAME;
extern const std::string DEFAULT_ARMY_NAME;
extern const std::string INVALID_NAME;

extern const std::string DEMON_TYPE_NAME;
extern const std::string BALROG_TYPE_NAME;
extern const std::string ELF_TYPE_NAME;
extern const std::string CYBERELF_TYPE_NAME;

extern const std::string MENU_TEXT;
extern const std::string FIRST_ARMY_QUESTION;
extern const std::string SECOND_ARMY_QUESTION;
extern const std::string ARMY_SIZE_QUESTION;

extern const std::string ARMY_ONE_BEFORE_HEADING;
extern const std::string ARMY_TWO_BEFORE_HEADING;
extern const std::string ARMY_ONE_AFTER_HEADING;
extern const std::string ARMY_TWO_AFTER_HEADING;

extern const std::string INVALID_MENU_MESSAGE;
extern const std::string INVALID_NAME_MESSAGE;
extern const std::string INVALID_SIZE_MESSAGE;
extern const std::string INVALID_ARMY_MESSAGE;
extern const std::string INVALID_CREATURE_MESSAGE;
extern const std::string INPUT_FILE_ERROR_MESSAGE;
extern const std::string CREATURE_FILE_ERROR_MESSAGE;
extern const std::string MEMORY_ERROR_MESSAGE;
extern const std::string PROGRAM_ERROR_MESSAGE;
extern const std::string BATTLE_ERROR_MESSAGE;
extern const std::string QUIT_MESSAGE;
extern const std::string TIE_MESSAGE;
extern const std::string WINNER_MESSAGE;
extern const std::string POSITION_WINNER_MESSAGE;
extern const std::string ROUND_WORD;
extern const std::string ROUNDS_WORD;

extern const int INVALID_STAT;
extern const int DEFAULT_STAT;
extern const int MIN_HEALTH;
extern const int MIN_VALID_STRENGTH;
extern const int MIN_RESET_STAT;
extern const int MAX_RESET_STAT;
extern const int MIN_ARMY_STAT;
extern const int MAX_ARMY_STAT;
extern const int MIN_ARMY_SIZE;

extern const int DEMON_ATTACK_CHANCE;
extern const int ELF_ATTACK_CHANCE;
extern const int CYBERELF_ATTACK_CHANCE;
extern const int DEMON_BONUS_DAMAGE;
extern const int CYBERELF_BONUS_DAMAGE;
extern const int ELF_DAMAGE_MULTIPLIER;
extern const int PERCENT_RANGE;

extern const int CREATURE_WIDTH;
extern const int TYPE_WIDTH;
extern const int NUMBER_WIDTH;
extern const int ROUND_WIDTH;
extern const int ARMY_WIDTH;
extern const int FIGHTER_WIDTH;
extern const int DAMAGE_WIDTH;
extern const int HEALTH_WIDTH;
extern const int SEPARATOR_WIDTH;
extern const int CREATURE_TABLE_WIDTH;
extern const int BATTLE_TABLE_WIDTH;

void displayMenu();
void clearCin(const std::string &errorMessage);
std::string getArmyName(const std::string &question);
int getArmySize();
bool isValidName(const std::string &proposedName);
int randomNumber(int minimum, int maximum);

#endif
