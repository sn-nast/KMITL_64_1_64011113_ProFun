#include "main.h"
#include "Move.h"
#include "Buffer.h"
#include "Control.h"
#include "Bomb.h"
#include "Map.h" 
#include "Object.h"
#include "Bot.h"

HANDLE wHnd;
HANDLE rHnd;
DWORD fdwMode;

CHAR_INFO consoleBuffer[SCREEN_WIDTH * SCREEN_HEIGHT];
COORD bufferSize = { SCREEN_WIDTH,SCREEN_HEIGHT };
COORD characterPos = { 0, 0 };
SMALL_RECT windowSize = { 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1 };

bool playStatus = true;
DWORD numEvents = 0;
DWORD numEventsRead = 0;

Player playerMe, * P_playerMe, playerBot[3];
Map nMap[5];

_Object
	Space = { ' ', NORMAL_ATTIBUTE, MAP_SPACE, NO_POINT},
	Wall[10] = {
		{ '#', 9,	CAN_DESTROY,	WALL_POINT },
		{ '|', 10,	CANt_DESTROY,	NO_POINT },
		{ '&', 11,	CANt_DESTROY,	NO_POINT },
		{ '$', 10,	CANt_DESTROY,	NO_POINT },
		{ '+', 11,	CANt_DESTROY,	NO_POINT },
		{ '%', 6,	CAN_DESTROY,	WALL_POINT },
		{ '=', 8,	CAN_DESTROY,	WALL_POINT },
		{ 13, 12,	CANt_DESTROY,	NO_POINT  }
	},
	Bomb_Nm		= {'@', 7,	BOMB_SHOW,	NO_POINT},
	Bomb_burst	= {'X', 4,	BOMB_BURST,	NO_POINT },
	Life		= { 3, 6,	CAN_KEEP,	ITEM_POINT },
	Potion		= { 'P', 11, CAN_KEEP,	ITEM_POINT},
	newBomb		= { 15, 12, CAN_KEEP,	ITEM_POINT }
;

int typeWall = sizeof(Wall) / sizeof(Wall[0]);

int main() {
	srand(time(NULL));

	setConsole(SCREEN_WIDTH, SCREEN_HEIGHT);
	setCursor(0);

	// Setup 
	strcpy_s(playerMe.Format, "Y");
	strcpy_s(playerMe.Name, "Me");
	playerMe.Position = {51, 16 };
	playerMe.Attribute = 7;
	playerMe.Lenght = 2;
	playerMe.Height = 2;
	playerMe.Bomb.Amount = 5;
	playerMe.Bomb.Time = 15;
	playerMe.SpeedX = 2;
	playerMe.SpeedY = 2;
	playerMe.Bomb.PowerX = 3;
	playerMe.Bomb.PowerY = 3;

	playerBot[0].Position = { 3, 1 };
	setupBot(&playerBot[0]);
	playerBot[0].Attribute = 180;
	setupBomb(&playerMe);
	setMode();
	//gotoxy(0, 0);
	//printf("[0 0]\n");
	//printf("[ v ]\n");
	//printf(" T T \n");
	// 
	//while() // เลือก map
	setupMap(&nMap[0], 1);

	while (playStatus /*&& playerMe.Life >= 0*/) {
		// Input Keyboard & Mouse events
		int Forwalk = rand();
		moveControl(&playerMe, &nMap[0]);

		if (Forwalk % 2 == 0) { moveBot(&playerBot[0], &nMap[0]); }
		dropBombBot(&playerBot[0], &nMap[0]);

		clearBuffer();

		changeStateMap(&nMap[0]);
		setOfBomb(&playerMe, &nMap[0]);

		setOfBot(&playerBot[0], &nMap[0]);
		playerMove(&playerMe, &nMap[0]);

		displayBuffer(); 

		//gotoxy(MAP_WIDTH + 10, 0);
		//printf_s("HELLO");
		Summary(&playerMe, { MAP_WIDTH, 2 });
		//Summary(&playerBot[0], { MAP_WIDTH, 15 });

		Sleep(150);
	}

	//clearBuffer();
	//displayBuffer();
	//gotoxy(0, 0);
	//printf_s("GAME OVER!!!")S;
	return 0;
}