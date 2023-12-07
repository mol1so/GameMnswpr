#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MINE 9

#define TRUE 1
#define FALSE 0

#define REVEALED 1
#define UNREVEALED 0

#define FLAGGED 1
#define UNFLAGGED 0

#define MODE_FLAG 1
#define MODE_REVEAL -1
#define MODE_CHANGE -5000

#define HAPPENED 1
#define NOT_HAPPENED 0

#define GAME_WIN 1
#define GAME_OVER -1
#define GAME_CONTINUE 0

#define GAME_NEW 1
#define GAME_END 0

#define USER_NICK_MAX_CHAR 20
#define USER_NICK_MAX_CHAR_PRINTF "\nEnter your nickname (up to 20 characters): "

#define MINUTE_DEFINED_IN_SECONDS 60
#define HOUR_DEFINED_IN_SECONDS 3600
#define DAY_DEFINED_IN_SECONDS 86400

//******************************
// Game difficulty             *
//******************************
extern char DIFFICULTY[13];
// Game difficulty is set to 'beginner', 'intermediate' or 'expert' based on user choice in: InputLib.cpp in setupDifficulty()
// Hardcoded maximum length to 13 characters -> longest word 'intermediate' -> 12 characters

//******************************
// Minefield parameters        *
//******************************
extern signed char ROWS, COLUMNS, MINE_COUNT;
// Minefield parameters are set in: InputLib.cpp in setupDifficulty() based on user choice -> Game difficulty

//******************************
// Minefield struct            *
//******************************
struct initializeMinefield {
	signed char game[16][30]; // Minefield (Array) used for game mechanics
	signed char mask[16][30]; // Is minefield.game[x][y] revealed/unrevealed?
	signed char flag[16][30]; // Is minefield.game[x][x] flagged/unflagged?
} extern minefield;
// Hardcoded maximum minefield dimensions to [16][30] -> Game difficulty = expert