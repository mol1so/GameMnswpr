#pragma once

void flushStdin();
void terminationCheck(int tryGet);

char* getUserNickname();

void setupDifficulty();

int getUserInputX(int *inputMode);
int getUserInputY(int *inputMode);

int chooseNewGameOrEnd(int *errorOpeningFile);