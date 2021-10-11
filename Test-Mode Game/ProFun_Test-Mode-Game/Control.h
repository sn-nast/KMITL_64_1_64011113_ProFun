#pragma once
#include "main.h"

void moveControl(Player* P_struct, Map* m);
void checkControl(int Direction, Player* p, Map* m);
int checkStateControl(unsigned int St);