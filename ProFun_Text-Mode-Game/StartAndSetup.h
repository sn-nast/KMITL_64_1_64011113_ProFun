#pragma once
#include "main.h"

void setAllScreen();
void setupPlayerToOrigin(Player* p);
void setupAllPlayerToOrigin();
void setupPlayerMe();
void homePage();
void controlSelectInHomePage(int sizeOption, int* nowSelected);
void gamePlayPageAndGameCheck();
void endGamePage();
void controlSelectInEndGame(int sizeOption, int* nowSelected);
void changeLevelPlayer();