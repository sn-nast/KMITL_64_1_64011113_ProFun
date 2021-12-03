#pragma once 
#include "main.h"

int setConsole(int x, int y);
int setMode(int mode);
void putBuffer(int x, int y, char ch, int atb);
void clearBuffer();
void clearScreen();
void displayBuffer();
void setCursor(bool visible);
void gotoxy(int x, int y);
void setcolor(int fg, int bg);
char cursor(int x, int y);
char cursorBuffer(COORD pos);
void convertToChar(int n, char* keepArray);
void printBuffer(COORD pos, char* text);
void printBuffer(COORD pos, int n);
