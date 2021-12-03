#pragma once
#include "main.h"

void dropObject(Map* m, COORD pos);
void keepObject(Player* p, Map* m);
void removeObject(Map* m, COORD pos);
void countDownObject(Player* p);
void countDownObjectAllPlayer();
void checkCountDrop(Map* m, int* randNextObj, bool mainPlayer);