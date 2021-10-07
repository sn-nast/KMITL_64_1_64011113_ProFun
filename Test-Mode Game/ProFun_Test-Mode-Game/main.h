#pragma once 
#include <Windows.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define SCREEN_WIDTH 120
#define SCREEN_HEIGHT 40
#define MAP_WIDTH 96
#define MAP_HEIGHT 32

const short NORMAL_ATTIBUTE = 7;
const char NORMAL_BOMB = '@';

const int MAP_SPACE = 0;

extern HANDLE wHnd;
extern HANDLE rHnd;
extern DWORD fdwMode;

extern CHAR_INFO consoleBuffer[];
extern COORD bufferSize;
extern COORD characterPos;
extern SMALL_RECT windowSize;

extern DWORD numEvents;
extern DWORD numEventsRead;

extern bool playStatus;

const short RIGHT_ARROW_1 = 16;
const short LEFT_ARROW_1 = 17;
const short UP_ARROW_1 = 30;
const short DOWN_ARROW_1 = 31;

const short RIGHT_ARROW_2 = 26;
const short LEFT_ARROW_2 = 27;
const short UP_ARROW_2 = 24;
const short DOWN_ARROW_2 = 25;

const short LEFT = 1;
const short RIGHT = 2;
const short DOWN = 3;
const short UP = 4;


typedef struct _Bomb{
	COORD Position[15];
	int Amount, Drop;
	int Power = 3;
	int State[15];
	int Time = 50;
	int CountDn[15];
}Bomb;

typedef struct _Player {
	char Format[5];
	unsigned int Lenght;
	unsigned int Height;
	COORD Position;
	COORD Last_position;
	COORD Direction;
	COORD Last_Direction;
	unsigned int SpeedX = 1;
	unsigned int SpeedY = 1;
	unsigned int Attribute;
	Bomb Bomb;
}Player;

struct _Object {
	char Format;
	int Attribute;
};

typedef struct _Map {
	unsigned int State[MAP_HEIGHT][MAP_WIDTH];
	_Object Object[MAP_HEIGHT][MAP_WIDTH];
}Map;

const char SYM_SHARP = '#';
const char SYM_POTION = 'P';
extern _Object Space, Wall_1, Wall_2, Potion;


