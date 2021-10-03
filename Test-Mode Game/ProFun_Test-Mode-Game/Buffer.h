#pragma once 

int setConsole(int x, int y);

int setMode();

void putBuffer(int x, int y, char ch, int atb);

void Display();

void setCursor(bool visible);

void gotoxy(int x, int y);

void setcolor(int fg, int bg);

char cursor(int x, int y);