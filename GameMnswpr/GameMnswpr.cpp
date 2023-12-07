// GameMnswpr.cpp : This file contains the "main" function. The program execution starts and ends here.
//

#include "GameMnswpr.h"
#include "MinefieldLib.h"
#include "InputLib.h"
#include "SystemLib.h"

// Global variables (constants)
struct initializeMinefield minefield;
signed char ROWS, COLUMNS, MINE_COUNT;
char DIFFICULTY[13];
// For more info see: 'GameMnswpr.h'

int checkInputModeChange(int a, char user[], int flagCount, int *inputMode) { // Input mode -> MODE_REVEAL / MODE_FLAG
	int inputModeTemp = *inputMode;
	while (a == MODE_CHANGE) {
		system("cls");
		flagCount = countAvailableFlags();

		printGameInfo();
		printGameStatus(user, flagCount, inputModeTemp);
		printMinefield();

		a = getUserInputX(&inputModeTemp);
		*inputMode = inputModeTemp;
	}
	return a;
}

int main()
{
	int errorOpeningFile = FALSE; 
	int infiniteProgramCycle = TRUE;
	char nick[USER_NICK_MAX_CHAR + 1]; // User nickname with a maximum length of 'USER_NICK_MAX_CHAR' characters
	int infiniteGameCycle, inputMode, firstRevealVar; // <-- variables that must be re-set each game

	int x, xNew, y, row, col;
	int gameState, flagCount;
	double successRate;
	unsigned long long int gameStartTime, gameEndTime;
	int programNewGameOrEnd;

	while (infiniteProgramCycle) {
		infiniteGameCycle = TRUE;
		inputMode = MODE_REVEAL;
		firstRevealVar = NOT_HAPPENED;

		// User setup:
		system("cls");
		printGameInfo();
		strcpy(nick, getUserNickname());
		setupDifficulty();

		// Game (first turn):
		system("cls");
		flagCount = countAvailableFlags();

		printGameInfo();
		printGameStatus(nick, flagCount, inputMode);

		preGenerateMinefield();
		generateMinefield();
		printMinefield();

		x = getUserInputX(&inputMode);
		xNew = checkInputModeChange(x, nick, flagCount, &inputMode);
		y = getUserInputY(&inputMode);
		col = xNew; // In the graphical representation of a minefield,
		row = y; // the rows with columns are reversed from the array definition => minefield[row][column]

		// The user can flag the field on the first turn instead of revealing it
		// => this can lead to the user revealing a mine on the first (!reveal!) turn and losing the game
		checkIfFirstRevealHappened(&firstRevealVar);
		if (firstRevealVar == NOT_HAPPENED) {
			gameStartTime = firstRevealField(row, col);
		}
		else {
			proccesField(row, col); // revealField() || flagField()
		}

		gameState = checkGameState(row, col);
		if (gameState == GAME_OVER || gameState == GAME_WIN) {
			infiniteGameCycle = FALSE;
		}

		// Game loop:
		while (infiniteGameCycle) {
			system("cls");
			flagCount = countAvailableFlags();

			printGameInfo();
			printGameStatus(nick, flagCount, inputMode);

			printMinefield();

			x = getUserInputX(&inputMode);
			xNew = checkInputModeChange(x, nick, flagCount, &inputMode);
			y = getUserInputY(&inputMode);
			col = xNew; // In the graphical representation of a minefield,
			row = y; // the rows with columns are reversed from the array definition => minefield[row][column]

			checkIfFirstRevealHappened(&firstRevealVar);
			if (firstRevealVar == NOT_HAPPENED) {
				gameStartTime = firstRevealField(row, col);
			}
			else {
				proccesField(row, col); // revealField() || flagField()
			}

			gameState = checkGameState(row, col);
			if (gameState == GAME_OVER || gameState == GAME_WIN) {
				infiniteGameCycle = FALSE;
			}
		}

		// Game over || Game win:
		system("cls");

		gameEndTime = time(NULL);
		calculateSuccessRate(&successRate);

		printGameInfo();
		printGameOverview(nick, &gameState, &gameStartTime, &gameEndTime, &successRate, &errorOpeningFile); // + save game summary to to the output stats file
		revealAndPrintEntireMinefield();

		// Start a new game or end the program?
		programNewGameOrEnd = chooseNewGameOrEnd(&errorOpeningFile);
		if (programNewGameOrEnd == GAME_END) {
			infiniteProgramCycle = FALSE;
		}
	}

	return 0;
}