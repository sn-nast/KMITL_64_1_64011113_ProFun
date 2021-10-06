#pragma once 
#include <Windows.h>
#include <stdio.h>
#include <string.h>

#define SCREEN_WIDTH 120
#define SCREEN_HEIGHT 40
#define MAP_WIDTH 96
#define MAP_HEIGHT 32

//const char SHARP_SYM '#'
//const char POTION_ 'P';

const short NORMAL_ATTIBUTE = 7;
const char NORMAL_BOMB = '@';

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

FILE* F;

struct _Bomb {
	COORD Position[15];
	int Amount;
	int Drop;
	int Power = 1;
	int State[15];
	int Time = 50;
	int CountDn[15];
};

struct Player {
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
	_Bomb Bomb;
};

struct _Map{
	const int Width = 96;
	const int Height = 32;
	char Format[32][96];
	unsigned int State[32][96];
	unsigned int Attribute[32][96];
};

typedef struct {
	const char Symbol;
	const int Attribute;
}_Object;

_Object Wall_1;
Wall_1 = { '#', NORMAL_ATTIBUTE };
Obj_Potion = { '#', NORMAL_ATTIBUTE };


