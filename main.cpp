/*
    CS 216 Lab #8 Abstract
    Muhammad Yusuf Rehman
*/

#include "functions.h"
#include "game.h"

#include <cstdlib>
#include <ctime>
#include <iostream>

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

    // Each class cleans up and reports its own allocation failures locally, so this
    // is the program-level bad_alloc handler required for every remaining allocation.
    try
    {
        do
        {
            displayMenu();
            cin >> menuChoice;

            switch (menuChoice)
            {
                case BATTLE:
                    game.playGame();
                    break;

                case QUIT:
                    cout << QUIT_MESSAGE;
                    break;

                default:
                    clearCin(INVALID_MENU_MESSAGE);
            }
        } while (menuChoice != QUIT && !cin.eof());
    }
    catch (const bad_alloc &)
    {
        cout << PROGRAM_ERROR_MESSAGE;
    }

    return 0;
}

/*
SAMPLE TEST RUNS - LAB #8 ABSTRACT

Compilation command used:
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp functions.cpp creature.cpp demon.cpp balrog.cpp elf.cpp cyberelf.cpp army.cpp game.cpp -o main.exe

The compilation shown above produced no warnings and no errors.
PowerShell prompts, file-rename commands, and compiler commands have been removed.
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

TEST RUN 3: INVALID ARMY SIZE AND 2-VS-2 BATTLE
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
Morgas             | Cyberelf       |          202 |          199
Thalia             | Cyberelf       |          182 |          187

Army #2 Stats before the Battle
Army: bLUE
Creature           | Type           |     Strength |       Health
-----------------------------------------------------------------
Kael               | Elf            |           62 |          241
Lyra               | Elf            |           64 |          203

Position 1 Battle
Round    | Atk Army         | Attacker                     |     Damage | Def Army         | Defender                     |  Health Before |   Health After
-----------------------------------------------------------------------------------------------------------------------------------------------------------
1        | rED              | Morgas the Cyberelf          |        145 | bLUE             | Kael the Elf                 |            241 |             96
2        | bLUE             | Kael the Elf                 |         13 | rED              | Morgas the Cyberelf          |            199 |            186
3        | rED              | Morgas the Cyberelf          |         21 | bLUE             | Kael the Elf                 |             96 |             75
4        | bLUE             | Kael the Elf                 |          1 | rED              | Morgas the Cyberelf          |            186 |            185
5        | rED              | Morgas the Cyberelf          |        147 | bLUE             | Kael the Elf                 |             75 |              0
Morgas the Cyberelf of rED won this position battle in 5 rounds.

Position 2 Battle
Round    | Atk Army         | Attacker                     |     Damage | Def Army         | Defender                     |  Health Before |   Health After
-----------------------------------------------------------------------------------------------------------------------------------------------------------
1        | rED              | Thalia the Cyberelf          |         58 | bLUE             | Lyra the Elf                 |            203 |            145
2        | bLUE             | Lyra the Elf                 |         90 | rED              | Thalia the Cyberelf          |            187 |             97
3        | rED              | Thalia the Cyberelf          |        168 | bLUE             | Lyra the Elf                 |            145 |              0
Thalia the Cyberelf of rED won this position battle in 3 rounds.

Army #1 Stats after the Battle
Army: rED
Creature           | Type           |     Strength |       Health
-----------------------------------------------------------------
Morgas             | Cyberelf       |          202 |          185
Thalia             | Cyberelf       |          182 |           97

Army #2 Stats after the Battle
Army: bLUE
Creature           | Type           |     Strength |       Health
-----------------------------------------------------------------
Kael               | Elf            |           62 |            0
Lyra               | Elf            |           64 |            0

rED overall health: 282
bLUE overall health: 0
rED is the winning army.


Menu:
1. Battle
2. Quit
Enter your choice: 2
Program ended.

TEST RUN 4: 10-VS-10 BATTLE WITH ALL DERIVED TYPES
Purpose: Verifies an arbitrary larger Army size, dynamic polymorphic creation of Demon, Balrog, Elf, and Cyberelf objects, and final health totals.

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
Morgas             | Demon          |          228 |           91
Thalia             | Demon          |          238 |          107
Kael               | Cyberelf       |          245 |          154
Lyra               | Cyberelf       |           49 |          175
Darius             | Elf            |          224 |          139
Selene             | Demon          |          231 |          214
Orion              | Elf            |          113 |          260
Freya              | Demon          |           51 |           52
Ronan              | Elf            |          262 |          161
Elara              | Elf            |          194 |          125

Army #2 Stats before the Battle
Army: Silver
Creature           | Type           |     Strength |       Health
-----------------------------------------------------------------
Cassian            | Balrog         |          159 |          121
Nerissa            | Balrog         |           63 |          275
Draven             | Cyberelf       |          143 |          264
Aria               | Elf            |          181 |          256
Magnus             | Demon          |          200 |          104
Vesper             | Balrog         |           49 |          172
Lucian             | Balrog         |          110 |          182
Isolde             | Demon          |          175 |          222
Talon              | Cyberelf       |           56 |           98
Eira               | Balrog         |          165 |          123

Position 1 Battle
Round    | Atk Army         | Attacker                     |     Damage | Def Army         | Defender                     |  Health Before |   Health After
-----------------------------------------------------------------------------------------------------------------------------------------------------------
1        | Gold             | Morgas the Demon             |        116 | Silver           | Cassian the Balrog           |            121 |              5
2        | Silver           | Cassian the Balrog           |        120 | Gold             | Morgas the Demon             |             91 |              0
Cassian the Balrog of Silver won this position battle in 2 rounds.

Position 2 Battle
Round    | Atk Army         | Attacker                     |     Damage | Def Army         | Defender                     |  Health Before |   Health After
-----------------------------------------------------------------------------------------------------------------------------------------------------------
1        | Gold             | Thalia the Demon             |        100 | Silver           | Nerissa the Balrog           |            275 |            175
2        | Silver           | Nerissa the Balrog           |         61 | Gold             | Thalia the Demon             |            107 |             46
3        | Gold             | Thalia the Demon             |         51 | Silver           | Nerissa the Balrog           |            175 |            124
4        | Silver           | Nerissa the Balrog           |         54 | Gold             | Thalia the Demon             |             46 |              0
Nerissa the Balrog of Silver won this position battle in 4 rounds.

Position 3 Battle
Round    | Atk Army         | Attacker                     |     Damage | Def Army         | Defender                     |  Health Before |   Health After
-----------------------------------------------------------------------------------------------------------------------------------------------------------
1        | Gold             | Kael the Cyberelf            |        100 | Silver           | Draven the Cyberelf          |            264 |            164
2        | Silver           | Draven the Cyberelf          |        114 | Gold             | Kael the Cyberelf            |            154 |             40
3        | Gold             | Kael the Cyberelf            |        209 | Silver           | Draven the Cyberelf          |            164 |              0
Kael the Cyberelf of Gold won this position battle in 3 rounds.

Position 4 Battle
Round    | Atk Army         | Attacker                     |     Damage | Def Army         | Defender                     |  Health Before |   Health After
-----------------------------------------------------------------------------------------------------------------------------------------------------------
1        | Gold             | Lyra the Cyberelf            |         11 | Silver           | Aria the Elf                 |            256 |            245
2        | Silver           | Aria the Elf                 |         82 | Gold             | Lyra the Cyberelf            |            175 |             93
3        | Gold             | Lyra the Cyberelf            |          4 | Silver           | Aria the Elf                 |            245 |            241
4        | Silver           | Aria the Elf                 |         87 | Gold             | Lyra the Cyberelf            |             93 |              6
5        | Gold             | Lyra the Cyberelf            |         12 | Silver           | Aria the Elf                 |            241 |            229
6        | Silver           | Aria the Elf                 |        154 | Gold             | Lyra the Cyberelf            |              6 |              0
Aria the Elf of Silver won this position battle in 6 rounds.

Position 5 Battle
Round    | Atk Army         | Attacker                     |     Damage | Def Army         | Defender                     |  Health Before |   Health After
-----------------------------------------------------------------------------------------------------------------------------------------------------------
1        | Gold             | Darius the Elf               |         42 | Silver           | Magnus the Demon             |            104 |             62
2        | Silver           | Magnus the Demon             |         97 | Gold             | Darius the Elf               |            139 |             42
3        | Gold             | Darius the Elf               |        205 | Silver           | Magnus the Demon             |             62 |              0
Darius the Elf of Gold won this position battle in 3 rounds.

Position 6 Battle
Round    | Atk Army         | Attacker                     |     Damage | Def Army         | Defender                     |  Health Before |   Health After
-----------------------------------------------------------------------------------------------------------------------------------------------------------
1        | Gold             | Selene the Demon             |         81 | Silver           | Vesper the Balrog            |            172 |             91
2        | Silver           | Vesper the Balrog            |         28 | Gold             | Selene the Demon             |            214 |            186
3        | Gold             | Selene the Demon             |        190 | Silver           | Vesper the Balrog            |             91 |              0
Selene the Demon of Gold won this position battle in 3 rounds.

Position 7 Battle
Round    | Atk Army         | Attacker                     |     Damage | Def Army         | Defender                     |  Health Before |   Health After
-----------------------------------------------------------------------------------------------------------------------------------------------------------
1        | Gold             | Orion the Elf                |         92 | Silver           | Lucian the Balrog            |            182 |             90
2        | Silver           | Lucian the Balrog            |         61 | Gold             | Orion the Elf                |            260 |            199
3        | Gold             | Orion the Elf                |        110 | Silver           | Lucian the Balrog            |             90 |              0
Orion the Elf of Gold won this position battle in 3 rounds.

Position 8 Battle
Round    | Atk Army         | Attacker                     |     Damage | Def Army         | Defender                     |  Health Before |   Health After
-----------------------------------------------------------------------------------------------------------------------------------------------------------
1        | Gold             | Freya the Demon              |          5 | Silver           | Isolde the Demon             |            222 |            217
2        | Silver           | Isolde the Demon             |        115 | Gold             | Freya the Demon              |             52 |              0
Isolde the Demon of Silver won this position battle in 2 rounds.

Position 9 Battle
Round    | Atk Army         | Attacker                     |     Damage | Def Army         | Defender                     |  Health Before |   Health After
-----------------------------------------------------------------------------------------------------------------------------------------------------------
1        | Gold             | Ronan the Elf                |         73 | Silver           | Talon the Cyberelf           |             98 |             25
2        | Silver           | Talon the Cyberelf           |         55 | Gold             | Ronan the Elf                |            161 |            106
3        | Gold             | Ronan the Elf                |         62 | Silver           | Talon the Cyberelf           |             25 |              0
Ronan the Elf of Gold won this position battle in 3 rounds.

Position 10 Battle
Round    | Atk Army         | Attacker                     |     Damage | Def Army         | Defender                     |  Health Before |   Health After
-----------------------------------------------------------------------------------------------------------------------------------------------------------
1        | Gold             | Elara the Elf                |        170 | Silver           | Eira the Balrog              |            123 |              0
Elara the Elf of Gold won this position battle in 1 round.

Army #1 Stats after the Battle
Army: Gold
Creature           | Type           |     Strength |       Health
-----------------------------------------------------------------
Morgas             | Demon          |          228 |            0
Thalia             | Demon          |          238 |            0
Kael               | Cyberelf       |          245 |           40
Lyra               | Cyberelf       |           49 |            0
Darius             | Elf            |          224 |           42
Selene             | Demon          |          231 |          186
Orion              | Elf            |          113 |          199
Freya              | Demon          |           51 |            0
Ronan              | Elf            |          262 |          106
Elara              | Elf            |          194 |          125

Army #2 Stats after the Battle
Army: Silver
Creature           | Type           |     Strength |       Health
-----------------------------------------------------------------
Cassian            | Balrog         |          159 |            5
Nerissa            | Balrog         |           63 |          124
Draven             | Cyberelf       |          143 |            0
Aria               | Elf            |          181 |          229
Magnus             | Demon          |          200 |            0
Vesper             | Balrog         |           49 |            0
Lucian             | Balrog         |          110 |            0
Isolde             | Demon          |          175 |          217
Talon              | Cyberelf       |           56 |            0
Eira               | Balrog         |          165 |            0

Gold overall health: 698
Silver overall health: 575
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
Morgas             | Cyberelf       |           59 |          114
Thalia             | Demon          |           75 |          169

Army #2 Stats before the Battle
Army: Second
Creature           | Type           |     Strength |       Health
-----------------------------------------------------------------
Kael               | Cyberelf       |           82 |          139
Lyra               | Demon          |          217 |          137

Position 1 Battle
Round    | Atk Army         | Attacker                     |     Damage | Def Army         | Defender                     |  Health Before |   Health After
-----------------------------------------------------------------------------------------------------------------------------------------------------------
1        | First            | Morgas the Cyberelf          |        106 | Second           | Kael the Cyberelf            |            139 |             33
2        | Second           | Kael the Cyberelf            |         34 | First            | Morgas the Cyberelf          |            114 |             80
3        | First            | Morgas the Cyberelf          |         43 | Second           | Kael the Cyberelf            |             33 |              0
Morgas the Cyberelf of First won this position battle in 3 rounds.

Position 2 Battle
Round    | Atk Army         | Attacker                     |     Damage | Def Army         | Defender                     |  Health Before |   Health After
-----------------------------------------------------------------------------------------------------------------------------------------------------------
1        | First            | Thalia the Demon             |         58 | Second           | Lyra the Demon               |            137 |             79
2        | Second           | Lyra the Demon               |        122 | First            | Thalia the Demon             |            169 |             47
3        | First            | Thalia the Demon             |         12 | Second           | Lyra the Demon               |             79 |             67
4        | Second           | Lyra the Demon               |        167 | First            | Thalia the Demon             |             47 |              0
Lyra the Demon of Second won this position battle in 4 rounds.

Army #1 Stats after the Battle
Army: First
Creature           | Type           |     Strength |       Health
-----------------------------------------------------------------
Morgas             | Cyberelf       |           59 |           80
Thalia             | Demon          |           75 |            0

Army #2 Stats after the Battle
Army: Second
Creature           | Type           |     Strength |       Health
-----------------------------------------------------------------
Kael               | Cyberelf       |           82 |            0
Lyra               | Demon          |          217 |           67

First overall health: 80
Second overall health: 67
First is the winning army.


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
Morgas             | Elf            |          141 |          154
Thalia             | Elf            |          268 |          209

Army #2 Stats before the Battle
Army: Fourth
Creature           | Type           |     Strength |       Health
-----------------------------------------------------------------
Kael               | Elf            |          202 |          197
Lyra               | Cyberelf       |           79 |          232

Position 1 Battle
Round    | Atk Army         | Attacker                     |     Damage | Def Army         | Defender                     |  Health Before |   Health After
-----------------------------------------------------------------------------------------------------------------------------------------------------------
1        | Third            | Morgas the Elf               |         74 | Fourth           | Kael the Elf                 |            197 |            123
2        | Fourth           | Kael the Elf                 |        109 | Third            | Morgas the Elf               |            154 |             45
3        | Third            | Morgas the Elf               |        276 | Fourth           | Kael the Elf                 |            123 |              0
Morgas the Elf of Third won this position battle in 3 rounds.

Position 2 Battle
Round    | Atk Army         | Attacker                     |     Damage | Def Army         | Defender                     |  Health Before |   Health After
-----------------------------------------------------------------------------------------------------------------------------------------------------------
1        | Third            | Thalia the Elf               |        169 | Fourth           | Lyra the Cyberelf            |            232 |             63
2        | Fourth           | Lyra the Cyberelf            |         25 | Third            | Thalia the Elf               |            209 |            184
3        | Third            | Thalia the Elf               |         37 | Fourth           | Lyra the Cyberelf            |             63 |             26
4        | Fourth           | Lyra the Cyberelf            |        192 | Third            | Thalia the Elf               |            184 |              0
Lyra the Cyberelf of Fourth won this position battle in 4 rounds.

Army #1 Stats after the Battle
Army: Third
Creature           | Type           |     Strength |       Health
-----------------------------------------------------------------
Morgas             | Elf            |          141 |           45
Thalia             | Elf            |          268 |            0

Army #2 Stats after the Battle
Army: Fourth
Creature           | Type           |     Strength |       Health
-----------------------------------------------------------------
Kael               | Elf            |          202 |            0
Lyra               | Cyberelf       |           79 |           26

Third overall health: 45
Fourth overall health: 26
Third is the winning army.


Menu:
1. Battle
2. Quit
Enter your choice: 2
Program ended.

TEST RUN 6: INSUFFICIENT CREATURE NAMES
Purpose: Verifies that requesting more creatures than the input file can supply is reported safely without a crash or a memory leak.

CS 216 Lab #8 Abstract
Muhammad Yusuf Rehman


Menu:
1. Battle
2. Quit
Enter your choice: 1
Enter the first army name: Big
Enter the second army name: Huge
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

*/
