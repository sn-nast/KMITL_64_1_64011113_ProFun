#pragma once
#include "main.h"

void setupBomb(Player* p);
void setOfBomb(Player* p, Map* m);
void dropBomb(Player* p, Map* m);
void checkBomb(Player* p, Map* m);
void showBomb(Player* p, Map* m);
void burstBomb(Player* p, int i, Map* m);