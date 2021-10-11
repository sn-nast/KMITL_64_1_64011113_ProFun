#pragma once
#include "main.h"

void setupBomb(Player* p);
void dropBomb(Player* p, Map* m);
void checkBomb(Player* p, Map* m);
void showBomb(Player* p, Map* m);
void showBomb(COORD pos);
void burstBomb(Player* p, int i, Map* m);