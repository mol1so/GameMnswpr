#pragma once

void preGenerateMinefield();
void generateMinefield();

void modifyUserInput(int inputA, int inputB, int *modifiedA, int *modifiedB);

int countAvailableFlags();

void printMinefield();

void revealField(int x, int y);
void flagField(int x, int y);
void proccesField(int x, int y);

int firstRevealField(int x, int y);

void checkIfFirstRevealHappened(int *firstRevealVar);
int checkGameState(int x, int y);

void calculateSuccessRate(double *successRate);
void revealAndPrintEntireMinefield();