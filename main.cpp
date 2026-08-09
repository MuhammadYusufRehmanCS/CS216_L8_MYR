/*
    CS 216 Lab #8 Abstract
    Muhammad Yusuf Rehman
*/

#include "functions.h"
#include "game.h"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <new>

using namespace std;

// Description: Runs the menu-driven abstract Creature program and handles bad_alloc as required by Lab #8.
// Precondition: Standard input and output are available.
// Postcondition: The user may create and battle Armies repeatedly until Quit is selected.
int main()
{
    int menuChoice = 0;
    Game game;

    srand(static_cast<unsigned int>(time(nullptr)));
    cout << LAB_NAME << '\n' << STUDENT_NAME << '\n';

    try
    {
        do
        {
            displayMenu();
            menuChoice = 0;
            cin >> menuChoice;

            switch (menuChoice)
            {
                case BATTLE:
                    game.playGame();
                    break;

                case QUIT:
                    cout << "Program ended.\n";
                    break;

                default:
                    clearCin(INVALID_MENU_MESSAGE);
            }
        } while (menuChoice != QUIT);
    }
    catch (const bad_alloc &)
    {
        cout << MEMORY_ERROR_MESSAGE << '\n';
    }

    return 0;
}
/*
SAMPLE TEST RUNS - LAB #8 ABSTRACT

Compilation command used:
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp functions.cpp creature.cpp demon.cpp balrog.cpp elf.cpp cyberelf.cpp army.cpp game.cpp -o main.exe

The compilation commands shown in the terminal produced no warnings or errors.
PowerShell prompts, file-rename commands, and compiler commands have been removed from the sample output.
Random creature types, statistics, and damage vary between runs.

TEST RUN 1: QUIT OPTION
Purpose: Verifies that menu option 2 exits the program normally.

CS 216 Lab #8 Abstract
Muhammad Yusuf Rehman


Menu:
1. Battle
2. Quit
Enter your choice: 2
Program ended.

TEST RUN 2: INVALID MENU INPUT
Purpose: Verifies that nonnumeric and out-of-range menu choices are rejected and the menu remains usable.

CS 216 Lab #8 Abstract
Muhammad Yusuf Rehman


Menu:
1. Battle
2. Quit
Enter your choice: X 
Invalid menu choice. Select from the menu above.


Menu:
1. Battle
2. Quit
Enter your choice: 0
Invalid menu choice. Select from the menu above.


Menu:
1. Battle
2. Quit
Enter your choice: 3
Invalid menu choice. Select from the menu above.


Menu:
1. Battle
2. Quit
Enter your choice: 2
Program ended.

TEST RUN 3: INVALID ARMY SIZE AND NORMAL 2-VS-2 BATTLE
Purpose: Verifies invalid Army-size input, dynamic creation of two Armies, a complete battle, nonnegative health, and the final Army winner.

CS 216 Lab #8 Abstract
Muhammad Yusuf Rehman


Menu:
1. Battle
2. Quit
Enter your choice: 1
Enter the first army name: rED
Enter the second army name: bLUE
Enter the number of creatures in each army: A
Enter a positive whole number.
Enter the number of creatures in each army: 0
Enter a positive whole number.
Enter the number of creatures in each army: -2
Enter a positive whole number.
Enter the number of creatures in each army: 2

Army #1 Stats before the Battle
Army: rED
Creature           | Type           |     Strength |       Health
-----------------------------------------------------------------
Morgas             | Cyberelf       |           73 |          168
Thalia             | Cyberelf       |          121 |          131

Army #2 Stats before the Battle
Army: bLUE
Creature           | Type           |     Strength |       Health
-----------------------------------------------------------------
Kael               | Demon          |          189 |           94
Lyra               | Elf            |           83 |          147

Position 1 Battle
Round    | Atk Army         | Attacker                     |     Damage | Def Army         | Defender                     |  Health Before |   Health After
-----------------------------------------------------------------------------------------------------------------------------------------------------------
1        | rED              | Morgas the Cyberelf          |         13 | bLUE             | Kael the Demon               |             94 |             81
2        | bLUE             | Kael the Demon               |         41 | rED              | Morgas the Cyberelf          |            168 |            127
3        | rED              | Morgas the Cyberelf          |         71 | bLUE             | Kael the Demon               |             81 |             10
4        | bLUE             | Kael the Demon               |        124 | rED              | Morgas the Cyberelf          |            127 |              3
5        | rED              | Morgas the Cyberelf          |         60 | bLUE             | Kael the Demon               |             10 |              0
Morgas the Cyberelf of rED won this position battle in 5 rounds.

Position 2 Battle
Round    | Atk Army         | Attacker                     |     Damage | Def Army         | Defender                     |  Health Before |   Health After
-----------------------------------------------------------------------------------------------------------------------------------------------------------
1        | rED              | Thalia the Cyberelf          |        156 | bLUE             | Lyra the Elf                 |            147 |              0
Thalia the Cyberelf of rED won this position battle in 1 round.

Army #1 Stats after the Battle
Army: rED
Creature           | Type           |     Strength |       Health
-----------------------------------------------------------------
Morgas             | Cyberelf       |           73 |            3
Thalia             | Cyberelf       |          121 |          131

Army #2 Stats after the Battle
Army: bLUE
Creature           | Type           |     Strength |       Health
-----------------------------------------------------------------
Kael               | Demon          |          189 |            0
Lyra               | Elf            |           83 |            0

rED overall health: 134
bLUE overall health: 0
rED is the winning army.


Menu:
1. Battle
2. Quit
Enter your choice: 2
Program ended.

TEST RUN 4: 10-VS-10 BATTLE WITH ALL DERIVED TYPES
Purpose: Verifies an arbitrary larger Army size, dynamic polymorphic creation of Demon, Balrog, Elf, and Cyberelf objects, complete battles, and final health totals.

CS 216 Lab #8 Abstract
Muhammad Yusuf Rehman


Menu:
1. Battle
2. Quit
Enter your choice: 1
Enter the first army name: Gold
Enter the second army name: Silver
Enter the number of creatures in each army: 10

Army #1 Stats before the Battle
Army: Gold
Creature           | Type           |     Strength |       Health
-----------------------------------------------------------------
Morgas             | Cyberelf       |          152 |          144
Thalia             | Balrog         |          256 |           56
Kael               | Elf            |          112 |          227
Lyra               | Demon          |          199 |           62
Darius             | Elf            |          265 |           60
Selene             | Demon          |          274 |          240
Orion              | Balrog         |           66 |          131
Freya              | Cyberelf       |          231 |           60
Ronan              | Elf            |          189 |          138
Elara              | Balrog         |           90 |          158

Army #2 Stats before the Battle
Army: Silver
Creature           | Type           |     Strength |       Health
-----------------------------------------------------------------
Cassian            | Elf            |          130 |          164
Nerissa            | Balrog         |          127 |          206
Draven             | Elf            |          133 |          204
Aria               | Cyberelf       |          167 |          101
Magnus             | Elf            |          124 |          184
Vesper             | Demon          |          165 |          139
Lucian             | Cyberelf       |          183 |          173
Isolde             | Elf            |          112 |          228
Talon              | Demon          |          193 |          225
Eira               | Cyberelf       |          177 |          247

Position 1 Battle
Round    | Atk Army         | Attacker                     |     Damage | Def Army         | Defender                     |  Health Before |   Health After
-----------------------------------------------------------------------------------------------------------------------------------------------------------
1        | Gold             | Morgas the Cyberelf          |         75 | Silver           | Cassian the Elf              |            164 |             89
2        | Silver           | Cassian the Elf              |         65 | Gold             | Morgas the Cyberelf          |            144 |             79
3        | Gold             | Morgas the Cyberelf          |         56 | Silver           | Cassian the Elf              |             89 |             33
4        | Silver           | Cassian the Elf              |         54 | Gold             | Morgas the Cyberelf          |             79 |             25
5        | Gold             | Morgas the Cyberelf          |         48 | Silver           | Cassian the Elf              |             33 |              0
Morgas the Cyberelf of Gold won this position battle in 5 rounds.

Position 2 Battle
Round    | Atk Army         | Attacker                     |     Damage | Def Army         | Defender                     |  Health Before |   Health After
-----------------------------------------------------------------------------------------------------------------------------------------------------------
1        | Gold             | Thalia the Balrog            |        263 | Silver           | Nerissa the Balrog           |            206 |              0
Thalia the Balrog of Gold won this position battle in 1 round.

Position 3 Battle
Round    | Atk Army         | Attacker                     |     Damage | Def Army         | Defender                     |  Health Before |   Health After
-----------------------------------------------------------------------------------------------------------------------------------------------------------
1        | Gold             | Kael the Elf                 |         58 | Silver           | Draven the Elf               |            204 |            146
2        | Silver           | Draven the Elf               |         10 | Gold             | Kael the Elf                 |            227 |            217
3        | Gold             | Kael the Elf                 |         37 | Silver           | Draven the Elf               |            146 |            109
4        | Silver           | Draven the Elf               |         70 | Gold             | Kael the Elf                 |            217 |            147
5        | Gold             | Kael the Elf                 |         73 | Silver           | Draven the Elf               |            109 |             36
6        | Silver           | Draven the Elf               |         75 | Gold             | Kael the Elf                 |            147 |             72
7        | Gold             | Kael the Elf                 |         60 | Silver           | Draven the Elf               |             36 |              0
Kael the Elf of Gold won this position battle in 7 rounds.

Position 4 Battle
Round    | Atk Army         | Attacker                     |     Damage | Def Army         | Defender                     |  Health Before |   Health After
-----------------------------------------------------------------------------------------------------------------------------------------------------------
1        | Gold             | Lyra the Demon               |        165 | Silver           | Aria the Cyberelf            |            101 |              0
Lyra the Demon of Gold won this position battle in 1 round.

Position 5 Battle
Round    | Atk Army         | Attacker                     |     Damage | Def Army         | Defender                     |  Health Before |   Health After
-----------------------------------------------------------------------------------------------------------------------------------------------------------
1        | Gold             | Darius the Elf               |        278 | Silver           | Magnus the Elf               |            184 |              0
Darius the Elf of Gold won this position battle in 1 round.

Position 6 Battle
Round    | Atk Army         | Attacker                     |     Damage | Def Army         | Defender                     |  Health Before |   Health After
-----------------------------------------------------------------------------------------------------------------------------------------------------------
1        | Gold             | Selene the Demon             |        241 | Silver           | Vesper the Demon             |            139 |              0
Selene the Demon of Gold won this position battle in 1 round.

Position 7 Battle
Round    | Atk Army         | Attacker                     |     Damage | Def Army         | Defender                     |  Health Before |   Health After
-----------------------------------------------------------------------------------------------------------------------------------------------------------
1        | Gold             | Orion the Balrog             |         44 | Silver           | Lucian the Cyberelf          |            173 |            129
2        | Silver           | Lucian the Cyberelf          |        116 | Gold             | Orion the Balrog             |            131 |             15
3        | Gold             | Orion the Balrog             |         63 | Silver           | Lucian the Cyberelf          |            129 |             66
4        | Silver           | Lucian the Cyberelf          |        136 | Gold             | Orion the Balrog             |             15 |              0
Lucian the Cyberelf of Silver won this position battle in 4 rounds.

Position 8 Battle
Round    | Atk Army         | Attacker                     |     Damage | Def Army         | Defender                     |  Health Before |   Health After
-----------------------------------------------------------------------------------------------------------------------------------------------------------
1        | Gold             | Freya the Cyberelf           |          9 | Silver           | Isolde the Elf               |            228 |            219
2        | Silver           | Isolde the Elf               |        142 | Gold             | Freya the Cyberelf           |             60 |              0
Isolde the Elf of Silver won this position battle in 2 rounds.

Position 9 Battle
Round    | Atk Army         | Attacker                     |     Damage | Def Army         | Defender                     |  Health Before |   Health After
-----------------------------------------------------------------------------------------------------------------------------------------------------------
1        | Gold             | Ronan the Elf                |         88 | Silver           | Talon the Demon              |            225 |            137
2        | Silver           | Talon the Demon              |        127 | Gold             | Ronan the Elf                |            138 |             11
3        | Gold             | Ronan the Elf                |         95 | Silver           | Talon the Demon              |            137 |             42
4        | Silver           | Talon the Demon              |         10 | Gold             | Ronan the Elf                |             11 |              1
5        | Gold             | Ronan the Elf                |        180 | Silver           | Talon the Demon              |             42 |              0
Ronan the Elf of Gold won this position battle in 5 rounds.

Position 10 Battle
Round    | Atk Army         | Attacker                     |     Damage | Def Army         | Defender                     |  Health Before |   Health After
-----------------------------------------------------------------------------------------------------------------------------------------------------------
1        | Gold             | Elara the Balrog             |        151 | Silver           | Eira the Cyberelf            |            247 |             96
2        | Silver           | Eira the Cyberelf            |        214 | Gold             | Elara the Balrog             |            158 |              0
Eira the Cyberelf of Silver won this position battle in 2 rounds.

Army #1 Stats after the Battle
Army: Gold
Creature           | Type           |     Strength |       Health
-----------------------------------------------------------------
Morgas             | Cyberelf       |          152 |           25
Thalia             | Balrog         |          256 |           56
Kael               | Elf            |          112 |           72
Lyra               | Demon          |          199 |           62
Darius             | Elf            |          265 |           60
Selene             | Demon          |          274 |          240
Orion              | Balrog         |           66 |            0
Freya              | Cyberelf       |          231 |            0
Ronan              | Elf            |          189 |            1
Elara              | Balrog         |           90 |            0

Army #2 Stats after the Battle
Army: Silver
Creature           | Type           |     Strength |       Health
-----------------------------------------------------------------
Cassian            | Elf            |          130 |            0
Nerissa            | Balrog         |          127 |            0
Draven             | Elf            |          133 |            0
Aria               | Cyberelf       |          167 |            0
Magnus             | Elf            |          124 |            0
Vesper             | Demon          |          165 |            0
Lucian             | Cyberelf       |          183 |           66
Isolde             | Elf            |          112 |          219
Talon              | Demon          |          193 |            0
Eira               | Cyberelf       |          177 |           96

Gold overall health: 516
Silver overall health: 381
Gold is the winning army.


Menu:
1. Battle
2. Quit
Enter your choice: 2
Program ended.

TEST RUN 5: REPEATED BATTLES IN ONE PROGRAM EXECUTION
Purpose: Verifies that the user can create new Armies and battle repeatedly without restarting the program.

CS 216 Lab #8 Abstract
Muhammad Yusuf Rehman


Menu:
1. Battle
2. Quit
Enter your choice: 1
Enter the first army name: First
Enter the second army name: Second
Enter the number of creatures in each army: 2

Army #1 Stats before the Battle
Army: First
Creature           | Type           |     Strength |       Health
-----------------------------------------------------------------
Morgas             | Balrog         |          194 |          254
Thalia             | Demon          |          183 |           70

Army #2 Stats before the Battle
Army: Second
Creature           | Type           |     Strength |       Health
-----------------------------------------------------------------
Kael               | Balrog         |          183 |          253
Lyra               | Demon          |          133 |          218

Position 1 Battle
Round    | Atk Army         | Attacker                     |     Damage | Def Army         | Defender                     |  Health Before |   Health After
-----------------------------------------------------------------------------------------------------------------------------------------------------------
1        | First            | Morgas the Balrog            |        214 | Second           | Kael the Balrog              |            253 |             39
2        | Second           | Kael the Balrog              |        264 | First            | Morgas the Balrog            |            254 |              0
Kael the Balrog of Second won this position battle in 2 rounds.

Position 2 Battle
Round    | Atk Army         | Attacker                     |     Damage | Def Army         | Defender                     |  Health Before |   Health After
-----------------------------------------------------------------------------------------------------------------------------------------------------------
1        | First            | Thalia the Demon             |        166 | Second           | Lyra the Demon               |            218 |             52
2        | Second           | Lyra the Demon               |         41 | First            | Thalia the Demon             |             70 |             29
3        | First            | Thalia the Demon             |         21 | Second           | Lyra the Demon               |             52 |             31
4        | Second           | Lyra the Demon               |         42 | First            | Thalia the Demon             |             29 |              0
Lyra the Demon of Second won this position battle in 4 rounds.

Army #1 Stats after the Battle
Army: First
Creature           | Type           |     Strength |       Health
-----------------------------------------------------------------
Morgas             | Balrog         |          194 |            0
Thalia             | Demon          |          183 |            0

Army #2 Stats after the Battle
Army: Second
Creature           | Type           |     Strength |       Health
-----------------------------------------------------------------
Kael               | Balrog         |          183 |           39
Lyra               | Demon          |          133 |           31

First overall health: 0
Second overall health: 70
Second is the winning army.


Menu:
1. Battle
2. Quit
Enter your choice: 1
Enter the first army name: Third
Enter the second army name: Fourth
Enter the number of creatures in each army: 2

Army #1 Stats before the Battle
Army: Third
Creature           | Type           |     Strength |       Health
-----------------------------------------------------------------
Morgas             | Elf            |           85 |          126
Thalia             | Cyberelf       |          144 |          149

Army #2 Stats before the Battle
Army: Fourth
Creature           | Type           |     Strength |       Health
-----------------------------------------------------------------
Kael               | Elf            |          138 |           92
Lyra               | Demon          |           96 |          166

Position 1 Battle
Round    | Atk Army         | Attacker                     |     Damage | Def Army         | Defender                     |  Health Before |   Health After
-----------------------------------------------------------------------------------------------------------------------------------------------------------
1        | Third            | Morgas the Elf               |         17 | Fourth           | Kael the Elf                 |             92 |             75
2        | Fourth           | Kael the Elf                 |         74 | Third            | Morgas the Elf               |            126 |             52
3        | Third            | Morgas the Elf               |          2 | Fourth           | Kael the Elf                 |             75 |             73
4        | Fourth           | Kael the Elf                 |         81 | Third            | Morgas the Elf               |             52 |              0
Kael the Elf of Fourth won this position battle in 4 rounds.

Position 2 Battle
Round    | Atk Army         | Attacker                     |     Damage | Def Army         | Defender                     |  Health Before |   Health After
-----------------------------------------------------------------------------------------------------------------------------------------------------------
1        | Third            | Thalia the Cyberelf          |        288 | Fourth           | Lyra the Demon               |            166 |              0
Thalia the Cyberelf of Third won this position battle in 1 round.

Army #1 Stats after the Battle
Army: Third
Creature           | Type           |     Strength |       Health
-----------------------------------------------------------------
Morgas             | Elf            |           85 |            0
Thalia             | Cyberelf       |          144 |          149

Army #2 Stats after the Battle
Army: Fourth
Creature           | Type           |     Strength |       Health
-----------------------------------------------------------------
Kael               | Elf            |          138 |           73
Lyra               | Demon          |           96 |            0

Third overall health: 149
Fourth overall health: 73
Third is the winning army.


Menu:
1. Battle
2. Quit
Enter your choice: 2
Program ended.

TEST RUN 6: INSUFFICIENT CREATURE NAMES
Purpose: Verifies that requesting more creatures than the input file can supply is handled safely without a crash.

CS 216 Lab #8 Abstract
Muhammad Yusuf Rehman


Menu:
1. Battle
2. Quit
Enter your choice: 1
Enter the first army name: LargeOne
Enter the second army name: LargeTWo
Enter the number of creatures in each army: 21
The army could not be generated from the creature-name file.


Menu:
1. Battle
2. Quit
Enter your choice: 2
Program ended.

TEST RUN 7: MISSING INPUT FILE
Purpose: Verifies that a missing in_names.txt file is reported safely and the program returns to the menu.
Note: in_names.txt was temporarily renamed for this test and restored immediately afterward.

CS 216 Lab #8 Abstract
Muhammad Yusuf Rehman


Menu:
1. Battle
2. Quit
Enter your choice: 1
The creature-name input file could not be opened.


Menu:
1. Battle
2. Quit
Enter your choice: 2
Program ended.

TEST RUN 8: FINAL CLEAN COMPILE AND QUIT
Purpose: Verifies the final multisource program still compiles with warning flags and exits normally after all testing.
Note: This run followed the final clean compilation using the command shown above.

CS 216 Lab #8 Abstract
Muhammad Yusuf Rehman


Menu:
1. Battle
2. Quit
Enter your choice: 2
Program ended.

*/