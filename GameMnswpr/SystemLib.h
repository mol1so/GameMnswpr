#pragma once

void printGameInfo();
void printGameStatus(char nick[], int flagCount, int inputMode);

void printGameOverview(char nick[], int *gameState, unsigned long long int *gameStartTime, unsigned long long int *gameEndTime, double *successRate, int *errorOpeningFile);