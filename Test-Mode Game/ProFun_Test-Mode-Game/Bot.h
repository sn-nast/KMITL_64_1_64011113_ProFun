#pragma once
#include "main.h"
#include "Move.h"

void setupBot(Player* p);
void setOfBot(Player* p, Map* m);
void moveBot(Player* p, Map* m);
void dropBombBot(Player* p, Map* m);
void checkBombBot(Player* p, Map* m, COORD* nearestBomb, double* distanceBomb);