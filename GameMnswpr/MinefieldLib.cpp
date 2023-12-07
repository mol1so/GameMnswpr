#include "GameMnswpr.h"

void preGenerateMinefield() {
    // Fill minefield.game with zeros 
    // (step required for minefield generation -> incrementation algorithm)
    // +
    // Fill minefield.mask with (zeros) -> 'UNREVEALED'
    // (everything is initially unrevealed in minefield.game)
    // +
    // Fill minefield.flag with (zeros) -> 'UNFLAGGED'
    // (everything is initially unflagged in minefield.game)
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLUMNS; ++j) {
            minefield.game[i][j] = 0;
            minefield.mask[i][j] = UNREVEALED;
            minefield.flag[i][j] = UNFLAGGED;
        }
    }
}

void generateMinefield() {
    // Placement of mines
    srand(time(NULL));
    for (int i = 0; i < MINE_COUNT; ++i) {
        int x = rand() % ROWS;
        int y = rand() % COLUMNS;
        while (minefield.game[x][y] == MINE) {
            x = rand() % ROWS;
            y = rand() % COLUMNS;
        }
        minefield.game[x][y] = MINE;

        // if - else:
        // (condition) ? (expression-true) : (expression-false)
        int rowS, columnS, rowEnd, columnEnd;
        (x > 0) ? (rowS = x - 1) : (rowS = 0);
        (x < ROWS - 1) ? (rowEnd = x + 1) : (rowEnd = ROWS - 1);
        (y > 0) ? (columnS = y - 1) : (columnS = 0);
        (y < COLUMNS - 1) ? (columnEnd = y + 1) : (columnEnd = COLUMNS - 1);

        // Incrementation of fields adjacent to the mine
        for (int i = rowS; i <= rowEnd; ++i) {
            for (int j = columnS; j <= columnEnd; ++j) {
                if (minefield.game[i][j] != MINE) {
                    ++minefield.game[i][j];
                }
            }
        }
        // Representation of the incrementation algorithm:
        // 
        //             column0       column1       column2  
        // 
        //         |-------------|-------------|-------------|                                          
        // row0    |rowS/columnS |             |columnEnd    |
        //         |-------------|-------------|-------------|
        // row1    |             |MINE         |             |
        //         |-------------|-------------|-------------|
        // row2    |rowEnd       |             |             |
        //         |-------------|-------------|-------------|
        //
        // The recursive revealing of adjacent fields
        // in the 'revealField()' function works on a similar principle
    }
}

void modifyUserInput(int inputA, int inputB, int *modifiedA, int *modifiedB) {
    // Modify 'inputA' and 'inputB' (x/y) for use with arrays that start with index 0
    --inputA;
    --inputB;
    *modifiedA = inputA;
    *modifiedB = inputB;
}

int countAvailableFlags() {
    int availableFlags = 0;
    int flags = 0;

    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLUMNS; ++j) {
            if (minefield.flag[i][j]) {
                ++flags;
            }
        }
    }
    availableFlags = MINE_COUNT - flags;

    return availableFlags;
}

void printMinefield() {
    // Graphics x-axis (hardcoded)
    if (DIFFICULTY[0] == 'b') { // Game difficulty = begginer
        printf("\n");
        printf("    ");
        for (int i = 0; i < COLUMNS; ++i) {
            printf(" X");
        }

        printf("\n");
        printf("    ");
        for (int i = 0; i < COLUMNS; ++i) {
            printf(" %i", i + 1);
        }
    }
    else { // Game difficulty = intermediate or expert
        printf("\n");
        printf("     ");
        for (int i = 0; i < COLUMNS; ++i) {
            printf(" X");
        }

        printf("\n");
        printf("     ");
        for (int i = 1; i < COLUMNS + 1; ++i) {
            if (i < 10) {
                printf(" 0");
            }
            else if (i >= 10 && i < 20) {
                printf(" 1");
            }
            else if (i >= 20 && i < 30) {
                printf(" 2");
            }
            else if (i == 30) {
                printf(" 3");
            }
        }

        printf("\n");
        printf("     ");
        int tempI = 1;
        for (int i = 0; i < COLUMNS; ++i) {
            printf(" %i", tempI);
            ++tempI;
            if (tempI == 10) {
                tempI = 0;
            }
        }
    }

    // Display the minefield
    printf("\n\n");
    for (int i = 0; i < ROWS; ++i) {
        // Print y-axis (hardcoded)
        if (DIFFICULTY[0] == 'b') { // Game difficulty = begginer
            printf(" Y");
            printf("%i ", i + 1);
        }
        else { // Game difficulty = intermediate or expert
            printf(" Y");
            if (i <= 8) {
                printf("0%i ", i + 1);
            }
            else {
                printf("%i ", i + 1);
            }
        }

        // Print minefield (not hardcoded)
        for (int j = 0; j < COLUMNS; ++j) {
            if (minefield.flag[i][j] == FLAGGED) {
                printf(" F");
            }
            else if (minefield.mask[i][j] == UNREVEALED && minefield.flag[i][j] == UNFLAGGED) {
                printf(" #");
            }
            else {
                if (minefield.game[i][j] == MINE) {
                    printf(" M");
                }
                else {
                    printf(" %i", minefield.game[i][j]);
                }
            }

            // End of row
            if (j == (COLUMNS - 1)) {
                printf("\n");
            }
        }
    }
}

void revealField(int x, int y) {
    // If the field is already revealed, do nothing / else unreveal it
    if (minefield.mask[x][y] == REVEALED) {
        return;
    }
    else {
        minefield.mask[x][y] = REVEALED;
        minefield.flag[x][y] = UNFLAGGED;
    }

    // Recursive unrevealing of adjacent fields
    if (minefield.game[x][y] == 0) {
        int rowS, columnS, rowEnd, columnEnd;
        (x > 0) ? (rowS = x - 1) : (rowS = 0);
        (x < ROWS - 1) ? (rowEnd = x + 1) : (rowEnd = ROWS - 1);
        (y > 0) ? (columnS = y - 1) : (columnS = 0);
        (y < COLUMNS - 1) ? (columnEnd = y + 1) : (columnEnd = COLUMNS - 1);

        for (int i = rowS; i <= rowEnd; ++i) {
            for (int j = columnS; j <= columnEnd; ++j) {
                if (minefield.mask[i][j] == UNREVEALED) {
                    revealField(i, j);
                }
            }
        }
    }
}

void flagField(int x, int y) {
    int flagCount = countAvailableFlags();

    // If the field is revealed, it cannot be flagged
    if (minefield.mask[x][y] == REVEALED) {
        return;
    }

    // Unflagging an already flagged field
    if (minefield.flag[x][y] == FLAGGED) {
        minefield.flag[x][y] = UNFLAGGED;
        return;
    }

    // If free flags are available, flag the field / else do nothing
    if (flagCount != 0) {
        minefield.flag[x][y] = FLAGGED;
    }
}

void proccesField(int x, int y) {
    // Input mode = MODE_FLAG
    if (x < 0 && y < 0) {
        // Revert x and y back to their original state
        // For more info see: 'InputLib.cpp -> getUserInputX()'
        x = -(x);
        y = -(y);

        int modifiedX, modifiedY;
        modifyUserInput(x, y, &modifiedX, &modifiedY);
        flagField(modifiedX, modifiedY);
    }

    // Input mode = MODE_REVEAL
    else {
        int modifiedX, modifiedY;
        modifyUserInput(x, y, &modifiedX, &modifiedY);
        revealField(modifiedX, modifiedY);
    }
}

int firstRevealField(int x, int y) {
    int modifiedX, modifiedY;
    modifyUserInput(x, y, &modifiedX, &modifiedY);

    // If the user reveals a mine on the first (!reveal!) turn, a new minefield is
    // generated to ensure that the user can never lose on the first (!reveal!) turn.
    while (minefield.game[modifiedX][modifiedY] == MINE) {
        // Reset minefield.game
        for (int i = 0; i < ROWS; ++i) {
            for (int j = 0; j < COLUMNS; ++j) {
                minefield.game[i][j] = 0;
            }
        }
        // Generate new minefield.game
        generateMinefield();
    }
    proccesField(x, y);

    int gameStartTime = time(NULL);
    return gameStartTime;
}

void checkIfFirstRevealHappened(int *firstRevealVar) {
    if (*firstRevealVar == NOT_HAPPENED) {
        for (int i = 0; i < ROWS; ++i) {
            for (int j = 0; j < COLUMNS; ++j) {
                if (minefield.mask[i][j] == REVEALED) {
                    *firstRevealVar = HAPPENED;
                    return;
                }
            }
        }
    }
}

int checkGameState(int x, int y) {
    int modifiedX, modifiedY;
    modifyUserInput(x, y, &modifiedX, &modifiedY);

    // Game over
    if (minefield.game[modifiedX][modifiedY] == MINE) {
        return GAME_OVER;
    }

    // Game win
    int revealedFields = 0;
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLUMNS; ++j) {
            if (minefield.mask[i][j] == REVEALED) {
                ++revealedFields;
            }
        }
    }

    if (revealedFields == ((ROWS * COLUMNS) - MINE_COUNT)) {
        return GAME_WIN;
    }

    // Game continue
    return GAME_CONTINUE;
}

void calculateSuccessRate(double *successRate) {
    double oneHundredPercentAmount = (ROWS * COLUMNS) - MINE_COUNT;
    double xPercentAmount = 0;
    double output;

    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLUMNS; ++j) {
            if (minefield.mask[i][j] == REVEALED) {
                ++xPercentAmount;
            }
        }
    }

    output = (xPercentAmount * 100) / oneHundredPercentAmount;
    *successRate = output;
}

void revealAndPrintEntireMinefield() {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLUMNS; ++j) {
            minefield.mask[i][j] = REVEALED;
            minefield.flag[i][j] = UNFLAGGED;
        }
    }
    printMinefield();
}