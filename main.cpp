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
    cout << LAB_NAME << STUDENT_NAME;

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
Morgas             | Cyberelf       |          210 |          208
Thalia             | Cyberelf       |          120 |          220

Army #2 Stats before the Battle
Army: bLUE
Creature           | Type           |     Strength |       Health
-----------------------------------------------------------------
Kael               | Elf            |          162 |          184
Lyra               | Demon          |          133 |          163

Position 1 Battle
Round    | Atk Army         | Attacker                     |     Damage | Def Army         | Defender                     |  Health Before |   Health After
-----------------------------------------------------------------------------------------------------------------------------------------------------------
1        | rED              | Morgas the Cyberelf          |        186 | bLUE             | Kael the Elf                 |            184 |              0
Morgas the Cyberelf of rED won this position battle in 1 round.

Position 2 Battle
Round    | Atk Army         | Attacker                     |     Damage | Def Army         | Defender                     |  Health Before |   Health After
-----------------------------------------------------------------------------------------------------------------------------------------------------------
1        | rED              | Thalia the Cyberelf          |         96 | bLUE             | Lyra the Demon               |            163 |             67
2        | bLUE             | Lyra the Demon               |         91 | rED              | Thalia the Cyberelf          |            220 |            129
3        | rED              | Thalia the Cyberelf          |         94 | bLUE             | Lyra the Demon               |             67 |              0
Thalia the Cyberelf of rED won this position battle in 3 rounds.

Army #1 Stats after the Battle
Army: rED
Creature           | Type           |     Strength |       Health
-----------------------------------------------------------------
Morgas             | Cyberelf       |          210 |          208
Thalia             | Cyberelf       |          120 |          129

Army #2 Stats after the Battle
Army: bLUE
Creature           | Type           |     Strength |       Health
-----------------------------------------------------------------
Kael               | Elf            |          162 |            0
Lyra               | Demon          |          133 |            0

rED overall health: 337
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
Morgas             | Cyberelf       |          210 |          208
Thalia             | Cyberelf       |          120 |          220
Kael               | Elf            |          162 |          184
Lyra               | Demon          |          133 |          163
Darius             | Elf            |          104 |          111
Selene             | Elf            |           86 |          260
Orion              | Balrog         |          261 |          254
Freya              | Elf            |          108 |           56
Ronan              | Demon          |          144 |          215
Elara              | Balrog         |          143 |          208

Army #2 Stats before the Battle
Army: Silver
Creature           | Type           |     Strength |       Health
-----------------------------------------------------------------
Cassian            | Balrog         |          144 |          189
Nerissa            | Elf            |          186 |          242
Draven             | Cyberelf       |          238 |           72
Aria               | Balrog         |          148 |          134
Magnus             | Cyberelf       |           49 |          113
Vesper             | Balrog         |          233 |          139
Lucian             | Elf            |          117 |           58
Isolde             | Demon          |           99 |           79
Talon              | Cyberelf       |          139 |          251
Eira               | Balrog         |          237 |          163

Position 1 Battle
Round    | Atk Army         | Attacker                     |     Damage | Def Army         | Defender                     |  Health Before |   Health After
-----------------------------------------------------------------------------------------------------------------------------------------------------------
1        | Gold             | Morgas the Cyberelf          |        193 | Silver           | Cassian the Balrog           |            189 |              0
Morgas the Cyberelf of Gold won this position battle in 1 round.

Position 2 Battle
Round    | Atk Army         | Attacker                     |     Damage | Def Army         | Defender                     |  Health Before |   Health After
-----------------------------------------------------------------------------------------------------------------------------------------------------------
1        | Gold             | Thalia the Cyberelf          |        212 | Silver           | Nerissa the Elf              |            242 |             30
2        | Silver           | Nerissa the Elf              |        158 | Gold             | Thalia the Cyberelf          |            220 |             62
3        | Gold             | Thalia the Cyberelf          |         71 | Silver           | Nerissa the Elf              |             30 |              0
Thalia the Cyberelf of Gold won this position battle in 3 rounds.

Position 3 Battle
Round    | Atk Army         | Attacker                     |     Damage | Def Army         | Defender                     |  Health Before |   Health After
-----------------------------------------------------------------------------------------------------------------------------------------------------------
1        | Gold             | Kael the Elf                 |        125 | Silver           | Draven the Cyberelf          |             72 |              0
Kael the Elf of Gold won this position battle in 1 round.

Position 4 Battle
Round    | Atk Army         | Attacker                     |     Damage | Def Army         | Defender                     |  Health Before |   Health After
-----------------------------------------------------------------------------------------------------------------------------------------------------------
1        | Gold             | Lyra the Demon               |         36 | Silver           | Aria the Balrog              |            134 |             98
2        | Silver           | Aria the Balrog              |        244 | Gold             | Lyra the Demon               |            163 |              0
Aria the Balrog of Silver won this position battle in 2 rounds.

Position 5 Battle
Round    | Atk Army         | Attacker                     |     Damage | Def Army         | Defender                     |  Health Before |   Health After
-----------------------------------------------------------------------------------------------------------------------------------------------------------
1        | Gold             | Darius the Elf               |         62 | Silver           | Magnus the Cyberelf          |            113 |             51
2        | Silver           | Magnus the Cyberelf          |         70 | Gold             | Darius the Elf               |            111 |             41
3        | Gold             | Darius the Elf               |         96 | Silver           | Magnus the Cyberelf          |             51 |              0
Darius the Elf of Gold won this position battle in 3 rounds.

Position 6 Battle
Round    | Atk Army         | Attacker                     |     Damage | Def Army         | Defender                     |  Health Before |   Health After
-----------------------------------------------------------------------------------------------------------------------------------------------------------
1        | Gold             | Selene the Elf               |         52 | Silver           | Vesper the Balrog            |            139 |             87
2        | Silver           | Vesper the Balrog            |         86 | Gold             | Selene the Elf               |            260 |            174
3        | Gold             | Selene the Elf               |         21 | Silver           | Vesper the Balrog            |             87 |             66
4        | Silver           | Vesper the Balrog            |        107 | Gold             | Selene the Elf               |            174 |             67
5        | Gold             | Selene the Elf               |         11 | Silver           | Vesper the Balrog            |             66 |             55
6        | Silver           | Vesper the Balrog            |        270 | Gold             | Selene the Elf               |             67 |              0
Vesper the Balrog of Silver won this position battle in 6 rounds.

Position 7 Battle
Round    | Atk Army         | Attacker                     |     Damage | Def Army         | Defender                     |  Health Before |   Health After
-----------------------------------------------------------------------------------------------------------------------------------------------------------
1        | Gold             | Orion the Balrog             |        362 | Silver           | Lucian the Elf               |             58 |              0
Orion the Balrog of Gold won this position battle in 1 round.

Position 8 Battle
Round    | Atk Army         | Attacker                     |     Damage | Def Army         | Defender                     |  Health Before |   Health After
-----------------------------------------------------------------------------------------------------------------------------------------------------------
1        | Gold             | Freya the Elf                |         52 | Silver           | Isolde the Demon             |             79 |             27
2        | Silver           | Isolde the Demon             |         59 | Gold             | Freya the Elf                |             56 |              0
Isolde the Demon of Silver won this position battle in 2 rounds.

Position 9 Battle
Round    | Atk Army         | Attacker                     |     Damage | Def Army         | Defender                     |  Health Before |   Health After
-----------------------------------------------------------------------------------------------------------------------------------------------------------
1        | Gold             | Ronan the Demon              |        130 | Silver           | Talon the Cyberelf           |            251 |            121
2        | Silver           | Talon the Cyberelf           |         60 | Gold             | Ronan the Demon              |            215 |            155
3        | Gold             | Ronan the Demon              |         97 | Silver           | Talon the Cyberelf           |            121 |             24
4        | Silver           | Talon the Cyberelf           |        130 | Gold             | Ronan the Demon              |            155 |             25
5        | Gold             | Ronan the Demon              |          7 | Silver           | Talon the Cyberelf           |             24 |             17
6        | Silver           | Talon the Cyberelf           |        180 | Gold             | Ronan the Demon              |             25 |              0
Talon the Cyberelf of Silver won this position battle in 6 rounds.

Position 10 Battle
Round    | Atk Army         | Attacker                     |     Damage | Def Army         | Defender                     |  Health Before |   Health After
-----------------------------------------------------------------------------------------------------------------------------------------------------------
1        | Gold             | Elara the Balrog             |        140 | Silver           | Eira the Balrog              |            163 |             23
2        | Silver           | Eira the Balrog              |        281 | Gold             | Elara the Balrog             |            208 |              0
Eira the Balrog of Silver won this position battle in 2 rounds.

Army #1 Stats after the Battle
Army: Gold
Creature           | Type           |     Strength |       Health
-----------------------------------------------------------------
Morgas             | Cyberelf       |          210 |          208
Thalia             | Cyberelf       |          120 |           62
Kael               | Elf            |          162 |          184
Lyra               | Demon          |          133 |            0
Darius             | Elf            |          104 |           41
Selene             | Elf            |           86 |            0
Orion              | Balrog         |          261 |          254
Freya              | Elf            |          108 |            0
Ronan              | Demon          |          144 |            0
Elara              | Balrog         |          143 |            0

Army #2 Stats after the Battle
Army: Silver
Creature           | Type           |     Strength |       Health
-----------------------------------------------------------------
Cassian            | Balrog         |          144 |            0
Nerissa            | Elf            |          186 |            0
Draven             | Cyberelf       |          238 |            0
Aria               | Balrog         |          148 |           98
Magnus             | Cyberelf       |           49 |            0
Vesper             | Balrog         |          233 |           55
Lucian             | Elf            |          117 |            0
Isolde             | Demon          |           99 |           27
Talon              | Cyberelf       |          139 |           17
Eira               | Balrog         |          237 |           23

Gold overall health: 749
Silver overall health: 220
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
Morgas             | Cyberelf       |          210 |          208
Thalia             | Cyberelf       |          120 |          220

Army #2 Stats before the Battle
Army: Second
Creature           | Type           |     Strength |       Health
-----------------------------------------------------------------
Kael               | Elf            |          162 |          184
Lyra               | Demon          |          133 |          163

Position 1 Battle
Round    | Atk Army         | Attacker                     |     Damage | Def Army         | Defender                     |  Health Before |   Health After
-----------------------------------------------------------------------------------------------------------------------------------------------------------
1        | First            | Morgas the Cyberelf          |        186 | Second           | Kael the Elf                 |            184 |              0
Morgas the Cyberelf of First won this position battle in 1 round.

Position 2 Battle
Round    | Atk Army         | Attacker                     |     Damage | Def Army         | Defender                     |  Health Before |   Health After
-----------------------------------------------------------------------------------------------------------------------------------------------------------
1        | First            | Thalia the Cyberelf          |         96 | Second           | Lyra the Demon               |            163 |             67
2        | Second           | Lyra the Demon               |         91 | First            | Thalia the Cyberelf          |            220 |            129
3        | First            | Thalia the Cyberelf          |         94 | Second           | Lyra the Demon               |             67 |              0
Thalia the Cyberelf of First won this position battle in 3 rounds.

Army #1 Stats after the Battle
Army: First
Creature           | Type           |     Strength |       Health
-----------------------------------------------------------------
Morgas             | Cyberelf       |          210 |          208
Thalia             | Cyberelf       |          120 |          129

Army #2 Stats after the Battle
Army: Second
Creature           | Type           |     Strength |       Health
-----------------------------------------------------------------
Kael               | Elf            |          162 |            0
Lyra               | Demon          |          133 |            0

First overall health: 337
Second overall health: 0
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
Morgas             | Demon          |          137 |          144
Thalia             | Demon          |          214 |          143

Army #2 Stats before the Battle
Army: Fourth
Creature           | Type           |     Strength |       Health
-----------------------------------------------------------------
Kael               | Cyberelf       |          208 |          144
Lyra               | Demon          |          119 |          186

Position 1 Battle
Round    | Atk Army         | Attacker                     |     Damage | Def Army         | Defender                     |  Health Before |   Health After
-----------------------------------------------------------------------------------------------------------------------------------------------------------
1        | Third            | Morgas the Demon             |         67 | Fourth           | Kael the Cyberelf            |            144 |             77
2        | Fourth           | Kael the Cyberelf            |         16 | Third            | Morgas the Demon             |            144 |            128
3        | Third            | Morgas the Demon             |         44 | Fourth           | Kael the Cyberelf            |             77 |             33
4        | Fourth           | Kael the Cyberelf            |        165 | Third            | Morgas the Demon             |            128 |              0
Kael the Cyberelf of Fourth won this position battle in 4 rounds.

Position 2 Battle
Round    | Atk Army         | Attacker                     |     Damage | Def Army         | Defender                     |  Health Before |   Health After
-----------------------------------------------------------------------------------------------------------------------------------------------------------
1        | Third            | Thalia the Demon             |        123 | Fourth           | Lyra the Demon               |            186 |             63
2        | Fourth           | Lyra the Demon               |        102 | Third            | Thalia the Demon             |            143 |             41
3        | Third            | Thalia the Demon             |        134 | Fourth           | Lyra the Demon               |             63 |              0
Thalia the Demon of Third won this position battle in 3 rounds.

Army #1 Stats after the Battle
Army: Third
Creature           | Type           |     Strength |       Health
-----------------------------------------------------------------
Morgas             | Demon          |          137 |            0
Thalia             | Demon          |          214 |           41

Army #2 Stats after the Battle
Army: Fourth
Creature           | Type           |     Strength |       Health
-----------------------------------------------------------------
Kael               | Cyberelf       |          208 |           33
Lyra               | Demon          |          119 |            0

Third overall health: 41
Fourth overall health: 33
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
