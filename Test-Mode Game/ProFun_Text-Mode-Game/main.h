#pragma once 
#include <Windows.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

#define SCREEN_WIDTH 120
#define SCREEN_HEIGHT 46
#define MAP_WIDTH	 50
#define MAP_HEIGHT	 41
#define MAP_WIDTH_3  50
#define MAP_HEIGHT_3 50


// Const of Bomb
const short NORMAL_ATTRIBUTE = 7;
const short NOW_BOMB = 10;
const short BOMB_CAN_PUT = 0;
const short BOMB_ALREADY_PUT = 1;
const short BOMB_COUNTING = 2;

// Const of State
const int CAN_KEEP = 12;
const int CAN_DESTROYED = 1;
const int CANt_DESTROYED = 2;
const int BOMB_SHOW = 7;
const int BOMB_BURST = 10;
const int MAP_SPACE = 0;

// Const of Object
const int NO_POINT = 0;
const int WALL_POINT = 100;
const int ITEM_POINT_NORMAL = 500;
const int ITEM_POINT_SPECIAL = 1000;

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
	
// Extern from Buffer
extern HANDLE wHnd;
extern HANDLE rHnd;
extern DWORD fdwMode;

extern CHAR_INFO consoleBuffer[];
extern COORD bufferSize;
extern COORD characterPos;
extern SMALL_RECT windowSize;

extern DWORD numEvents;
extern DWORD numEventsRead;

//Struct form
typedef struct _Bomb{
	COORD Position[15];
	unsigned int Amount, NewDrop;
	unsigned int Time;
	unsigned int State[15];
	unsigned int CountDn[15];
	unsigned int PowerX, PowerY;
	unsigned int CountBombDropNow;
} Bomb;

typedef struct _ForBot {
	unsigned int DirectionNow;
	unsigned int CountDirectionNow;
	unsigned int LastDirectionNow;
	unsigned int MaxCanMove[4];
	unsigned int CountMovedThisDirection[4];
	unsigned int CountCantMoveThisDirection[4];
	unsigned int MaxCanDropBomb;
	bool Alive;
	
} ForBot;

typedef struct _Player {
	char Name[30];
	char Format[5];
	unsigned int Lenght;
	unsigned int Height;
	unsigned int Dir_atb;
	unsigned int Attribute;
	COORD StartPositon;
	COORD Position;
	COORD Last_Position;
	COORD Direction;
	COORD Last_Direction;
	unsigned int SpeedX;
	unsigned int SpeedY;
	unsigned int Life;
	unsigned int Point;
	unsigned int DeathlessTime;
	unsigned int Call;
	Bomb Bomb;
	ForBot Bot;
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
	unsigned int OwnerBomb[MAP_HEIGHT][MAP_WIDTH];
	_Object Object[MAP_HEIGHT][MAP_WIDTH];
	int Time[MAP_HEIGHT][MAP_WIDTH];
	int ObjRand[MAP_HEIGHT][MAP_WIDTH];
	bool WarningLost[MAP_HEIGHT][MAP_WIDTH];
	int maxBombPowerX;
	int maxBombPowerY;
	unsigned int GameTime_Minute;
	unsigned int GameTime_Second;
	unsigned int CountDrop_Life;
	unsigned int CountDrop_newBomb;
	unsigned int CountDrop_Potion;
	unsigned int CountDrop_Deathless;

} Map;

struct _PointHistory {
	char Name[50];
	int Point;
};

// Extern Object
extern _Object Space, Bomb_Nm, Bomb_burst, Life, Potion, Wall[], newBomb, Deathless;
extern const int typeWall;

// Extern map
extern Map playMap[3];
extern bool timeUp;
extern bool timeChange;
extern bool winStatus;
const int NO_OWNER_BOMB = 0;
extern SHORT summaryLastLine;

// Extern Bot
extern Player playerBot[3];
extern const int amountBot;

// Extern Start and Setup
extern bool playStatus;
extern bool programStatus;
extern bool homePageStatus;
extern bool endGameStatus;

// About player
extern unsigned int countWin;
extern unsigned int countLost;
extern int mapSelected;
extern Player playerMe;
const int KILL_POINT = 5000;
extern unsigned int levelPlayer;