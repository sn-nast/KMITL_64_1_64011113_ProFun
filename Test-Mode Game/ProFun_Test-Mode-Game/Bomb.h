#pragma once
#include "main.h"

void setupBomb(Player* p);
void dropBomb(Player* p);
void checkBomb(Player* p);
void showBomb(Player* p);
void showBomb(COORD pos, char bomb);
void burstBomb(Player S, int i);