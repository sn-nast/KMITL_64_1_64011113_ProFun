#pragma once 
#include <Windows.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>

#define SCREEN_WIDTH 120
#define SCREEN_HEIGHT 40
#define MAP_WIDTH 80
#define MAP_HEIGHT 32

// Const of Bomb
const short NORMAL_ATTIBUTE = 7;
const char NORMAL_BOMB = '@';
const short NOW_BOMB = 10;

// Const of State
const int CAN_KEEP = 12;
const int CAN_DESTROY = 1;
const int CANt_DESTROY = 2;
const int BOMB_SHOW = 7;
const int BOMB_BURST = 10;
const int MAP_SPACE = 0;

// Const of Object
const int NO_POINT = 0;
const int WALL_POINT = 100;
const int ITEM_POINT = 1000;

// Const of Arrow
const short LEFT = 1;
const short RIGHT = 2;
const short DOWN = 3;
const short UP = 4;
// Type of Arrow
	const short RIGHT_ARROW_1 = 16;
	const short LEFT_ARROW_1 = 17;
	const short UP_ARROW_1 = 30;
	const short DOWN_ARROW_1 = 31;
	
	const short RIGHT_ARROW_2 = 26;
	const short LEFT_ARROW_2 = 27;
	const short UP_ARROW_2 = 24;
	const short DOWN_ARROW_2 = 25;
	
// Extern from main
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

//Struct form
typedef struct _Bomb{
	COORD Position[15];
	int Amount = 1, Drop = 0;
	int State[15];
	int Time = 15;
	int CountDn[15];
	int PowerX = 1, PowerY = 1;
} Bomb;

typedef struct _Player {
	char Name[20];
	char Format[5];
	unsigned int Lenght;
	unsigned int Height;
	COORD Position;
	COORD Last_position;
	COORD Direction;
	COORD Last_Direction;
	unsigned int Dir_atb = 4;
	unsigned int SpeedX = 1;
	unsigned int SpeedY = 1;
	unsigned int Attribute;
	Bomb Bomb;
	int Life = 1;
	long int Point;
} Player;

struct _Object {
	char Format;
	int Attribute;
	int NormalState;
	int Point;
};

typedef struct _Map {
	unsigned int State[MAP_HEIGHT][MAP_WIDTH];
	unsigned int LastState[MAP_HEIGHT][MAP_WIDTH];
	_Object Object[MAP_HEIGHT][MAP_WIDTH];
	int Time[MAP_HEIGHT][MAP_WIDTH];
	int ObjRand[MAP_HEIGHT][MAP_WIDTH];
} Map;

// Extern Object
extern _Object Space, Bomb_Nm, Bomb_burst, Life, Potion, Wall[], newBomb;
extern int typeWall;