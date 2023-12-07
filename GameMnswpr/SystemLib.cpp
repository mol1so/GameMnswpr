#include "GameMnswpr.h"

void printGameInfo() {
	printf("GameMnswpr\n");
	printf("Copyright (c) 2023 Oldrich Molis\n");
}

void printGameStatus(char nick[], int flagCount, int inputMode) {
	// User
	printf("\nUser: '%s'\n", nick);

	// Difficulty
	printf("Difficulty: %s\n", DIFFICULTY);

	// Flags available
	printf("Flags available: %i\n", flagCount);

	// Input mode
	if (inputMode == MODE_REVEAL) {
		printf("Mode (reveal/flag): reveal\n");
	}
	else {
		printf("Mode (reveal/flag): flag\n");
	}
}

// Displays game summary to the user and saves it to the output stats file
void printGameOverview(char nick[], int *gameState, unsigned long long int *gameStartTime, unsigned long long int *gameEndTime, double *successRate, int *errorOpeningFile) {
	// User
	printf("\nUser: '%s'\n", nick);
	
	// Difficulty
	printf("Difficulty: %s\n", DIFFICULTY);

	// Game result
	char gameResult[5];
	if (*gameState == GAME_OVER) {
		strcpy(gameResult, "loss");
	}
	else {
		strcpy(gameResult, "win");
	}
	printf("Game result: %s\n", gameResult);

	// Playtime
	struct calculatePlaytime {
		unsigned long long int seconds;

		unsigned long long int onlyMinutes;
		unsigned long long int onlyMinutesPlusSecondsLeftover;

		unsigned long long int onlyHours;
		unsigned long long int onlyHoursPlusMinutesLeftover;
		unsigned long long int onlyHoursPlusMinutesLeftoverPlusSecondsLeftover;
	} playtime;

	playtime.seconds = *gameEndTime - *gameStartTime;

	playtime.onlyMinutes = playtime.seconds / 60;
	playtime.onlyMinutesPlusSecondsLeftover = playtime.seconds % 60;

	playtime.onlyHours = playtime.seconds / (60 * 60);
	playtime.onlyHoursPlusMinutesLeftover = playtime.onlyMinutes % 60;
	playtime.onlyHoursPlusMinutesLeftoverPlusSecondsLeftover = playtime.seconds % 60;

	if (playtime.seconds >= DAY_DEFINED_IN_SECONDS) { // Playtime 24h+
		printf("Playtime: 24h+\n");
	}
	else if (playtime.seconds < MINUTE_DEFINED_IN_SECONDS) { // Playtime 0s - 59s
		printf("Playtime (hh:mm:ss): 00:00:%02lli\n", playtime.seconds);
	}
	else if (playtime.seconds >= MINUTE_DEFINED_IN_SECONDS && playtime.seconds < HOUR_DEFINED_IN_SECONDS) { // Playtime 0s - 59m
		printf("Playtime (hh:mm:ss): 00:%02lli:%02lli\n", playtime.onlyMinutes, playtime.onlyMinutesPlusSecondsLeftover);
	}
	else { // Playtime 0s - 23h:59m:59s
		printf("Playtime (hh:mm:ss): %02lli:%02lli:%02lli\n", playtime.onlyHours, playtime.onlyHoursPlusMinutesLeftover, playtime.onlyHoursPlusMinutesLeftoverPlusSecondsLeftover);
	}

	// Success rate
	printf("Success rate (revealed fields): %.2lf %%\n", *successRate);

	// Save game summary to the game stats file
	FILE *fptr;

	fptr = fopen("GameMnswprStats.txt", "a");
	if (fptr != NULL) {
		*errorOpeningFile = FALSE;

		// Playtime 24h+
		if (playtime.seconds >= DAY_DEFINED_IN_SECONDS) {
			fprintf(
				fptr,
				"[{'User': '%s'}, {'Difficulty': '%s'}, {'Game result': '%s'}, {'Playtime': '24h+'}, {'Success rate (revealed fields)': '%.2lf %%'}]\n",
				nick, DIFFICULTY, gameResult, *successRate
			);
		}
		// Playtime 0s - 59s
		else if (playtime.seconds < MINUTE_DEFINED_IN_SECONDS) {
			fprintf(
				fptr,
				"[{'User': '%s'}, {'Difficulty': '%s'}, {'Game result': '%s'}, {'Playtime (hh:mm:ss)': '00:00:%02lli'}, {'Success rate (revealed fields)': '%.2lf %%'}]\n",
				nick, DIFFICULTY, gameResult, playtime.seconds, *successRate
			);
		}
		// Playtime 0s - 59m
		else if (playtime.seconds >= MINUTE_DEFINED_IN_SECONDS && playtime.seconds < HOUR_DEFINED_IN_SECONDS) {
			fprintf(
				fptr,
				"[{'User': '%s'}, {'Difficulty': '%s'}, {'Game result': '%s'}, {'Playtime (hh:mm:ss)': '00:%02lli:%02lli'}, {'Success rate (revealed fields)': '%.2lf %%'}]\n",
				nick, DIFFICULTY, gameResult, playtime.onlyMinutes, playtime.onlyMinutesPlusSecondsLeftover, *successRate
			);
		}
		// Playtime 0s - 23h:59m:59s
		else {
			fprintf(
				fptr,
				"[{'User': '%s'}, {'Difficulty': '%s'}, {'Game result': '%s'}, {'Playtime (hh:mm:ss)': '%02lli:%02lli:%02lli'}, {'Success rate (revealed fields)': '%.2lf %%'}]\n",
				nick, DIFFICULTY, gameResult, playtime.onlyHours, playtime.onlyHoursPlusMinutesLeftover, playtime.onlyHoursPlusMinutesLeftoverPlusSecondsLeftover, *successRate
			);
		}
	}
	else {
		*errorOpeningFile = TRUE;
	}
	fclose(fptr);
}