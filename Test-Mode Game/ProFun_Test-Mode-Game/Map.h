#pragma once
#include "main.h"

void setupMap(Map* m, int n_map);
char planMap(int n, COORD pos);
void changeStateMap(Map* m); 
void Summary(Player* p, COORD pos);