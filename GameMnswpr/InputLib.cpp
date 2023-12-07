#include "GameMnswpr.h"

void flushStdin() {
    // Empty the input buffer
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void terminationCheck(int tryGet) {
    // Program termination -> infinite loop protection
    if (tryGet == 3) {
        printf("\nThe program has been terminated. You have entered an invalid entry three times in a row.\n");
        system("pause");
        exit(-1);
    }
}

char* getUserNickname() {
    // Retrieve a user nickname with a maximum length of 'USER_NICK_MAX_CHAR' characters
    char nick[USER_NICK_MAX_CHAR + 1];

    printf(USER_NICK_MAX_CHAR_PRINTF);
    fgets(nick, USER_NICK_MAX_CHAR + 1, stdin);
    nick[strcspn(nick, "\n")] = '\0';

    if (strlen(nick) == USER_NICK_MAX_CHAR) {
        flushStdin();
    }

    return nick;
}

void setupDifficulty() {
    // Game difficulty setting based on user choice
    enum difficulty {beginner = 1, intermediate, expert} difficultyVar;

    int sCount;
    char input[5];

    int tryGet = 0;
    while (tryGet != 3) {
        printf("\n('1' = Beginner, '2' = Intermediate, '3' = Expert)");
        printf("\nSelect the game difficulty, enter a number: ");

        fgets(input, 5, stdin);
        input[strcspn(input, "\n")] = '\0';
        sCount = sscanf(input, "%3i", &difficultyVar);

        if (sCount != 1 || difficultyVar < 1 || difficultyVar > 3) {
            if (strlen(input) == 4) {
                flushStdin();
            }
            printf("Error! Invalid game difficulty!\n");
        }
        else {
            if (strlen(input) == 4) {
                flushStdin();
            }
            break;
        }
        ++tryGet;
    }
    terminationCheck(tryGet);

    switch (difficultyVar) {
    case beginner:
        ROWS = 9;
        COLUMNS = 9;
        MINE_COUNT = 10;
        strcpy(DIFFICULTY, "beginner");
        break;
    case intermediate:
        ROWS = 16;
        COLUMNS = 16;
        MINE_COUNT = 40;
        strcpy(DIFFICULTY, "intermediate");
        break;
    case expert:
        ROWS = 16;
        COLUMNS = 30;
        MINE_COUNT = 99;
        strcpy(DIFFICULTY, "expert");
        break;
    }
}

// The getUserInputX() and getUserInputY() functions return negative values of the values entered by the user if the inputMode = MODE_FLAG
int getUserInputX(int *inputMode) {
    // Getting the X coordinate from the user || setting the input mode based on user choice 
    int x, output, sCount;
    char input[5];

    int tryGet = 0;
    printf("\nX = 'T' toggles between reveal and flag mode\n");
    printf("X = 'Q' terminates the game\n");
    while (tryGet != 3) {
        printf("\nX: ");

        fgets(input, 5, stdin);
        input[strcspn(input, "\n")] = '\0';
        sCount = sscanf(input, "%i", &x);

        // Game termination
        if (input[0] == 'Q' || input[0] == 'q') {
            if (strlen(input) == 4) {
                flushStdin();
            }
            printf("\nThe program has been terminated.\n");
            system("pause");
            exit(0);
        }
        // Input mode switch
        else if (input[0] == 'T' || input[0] == 't') {
            if (strlen(input) == 4) {
                flushStdin();
            }
            *inputMode = -(*inputMode); // MODE_REVEAL -> MODE_FLAG || MODE_FLAG -> MODE_REVEAL
            return MODE_CHANGE;
        }
        // X coordinate handling
        else if (sCount != 1 || x < 1 || x > COLUMNS) {
            if (strlen(input) == 4) {
                flushStdin();
            }
            printf("Error! Invalid command/coordinate!\n");
        }
        else {
            if (strlen(input) == 4) {
                flushStdin();
            }
            break;
        }
        ++tryGet;
    }
    terminationCheck(tryGet);
    
    if (*inputMode == MODE_FLAG) {
        output = -(x);
    }
    else {
        output = x;
    }

    return output;
}

int getUserInputY(int *inputMode) {
    // Getting the Y coordinate from the user
    int y, output, sCount;
    char input[5];

    int tryGet = 0;
    while (tryGet != 3) {
        printf("\nY: ");

        fgets(input, 5, stdin);
        input[strcspn(input, "\n")] = '\0';
        sCount = sscanf(input, "%i", &y);

        if (sCount != 1 || y < 1 || y > ROWS) {
            if (strlen(input) == 4) {
                flushStdin();
            }
            printf("Error! Invalid command/coordinate!\n");
        }
        else {
            if (strlen(input) == 4) {
                flushStdin();
            }
            break;
        }
        ++tryGet;
    }
    terminationCheck(tryGet);

    if (*inputMode == MODE_FLAG) {
        output = -(y);
    }
    else {
        output = y;
    }

    return output;
}

int chooseNewGameOrEnd(int *errorOpeningFile) {
    int output;
    char userInput[2];

    if (*errorOpeningFile == FALSE) {
        printf("\nThe game summary was saved in the game stats file.\n");
    }
    else {
        printf("\nAn error occurred while saving the game summary to the game stats file.\n");
    }
    printf("To start a new game, enter 'N', if you enter anything else the program will be terminated: ");

    fgets(userInput, 2, stdin);
    userInput[strcspn(userInput, "\n")] = '\0';

    if (strlen(userInput) == 1) {
        flushStdin();
    }

    if (userInput[0] == 'N' || userInput[0] == 'n') {
        output = GAME_NEW;
    }
    else {
        output = GAME_END;
    }

    return output;
}