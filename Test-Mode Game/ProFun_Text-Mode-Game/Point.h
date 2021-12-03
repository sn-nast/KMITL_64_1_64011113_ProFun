#pragma once
#include "main.h"

extern _PointHistory PointHistory[5];

void readPoint();
void arrangePoint();
void recordPoint(Player* p);
void showHighestPoint(COORD start);
