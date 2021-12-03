#pragma once
#include "main.h"
#include "Move.h"

void setupAllPlayerBot();
void setupPlayerBot(Player* p);
void setOfAllBot(Map* m);
void moveBot(Player* p, Map* m);
void moveAllBot(Map* m);
void checkBombAllBot(Map* m);
void summaryAllBot();
void dropBombBot(Player* p, Map* m);
void dropBombAllBot(Map* m);
void checkBombBot(Player* p, Map* m, COORD* nearestBomb, double* distanceBomb, const int sizeWantCheckBomb);
bool checkNearMainPlayer(Player* p, Map* m, int xCheck, int yCheck);
double findPlayerPostion(Player* p, COORD* posAnotherPlayer, int nPlayer);