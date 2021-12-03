#pragma once
#include "main.h"

void setupMap(Map* m, int n_map);
void countDownGameTime(Map* m);
char planMap(int n, COORD pos);
void changeStateMap(Map* m); 
void summary(Player* p, COORD pos);