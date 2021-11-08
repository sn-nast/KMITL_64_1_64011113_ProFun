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
COORD bufferSize = { SCREEN_WIDTH, SCREEN_HEIGHT };
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
		{ '#', 9,	CAN_DESTROYED,	WALL_POINT },
		{ '|', 10,	CANt_DESTROYED,	NO_POINT },
		{ '&', 11,	CANt_DESTROYED,	NO_POINT },
		{ '$', 10,	CANt_DESTROYED,	NO_POINT },
		{ '+', 11,	CANt_DESTROYED,	NO_POINT },
		{ '%', 6,	CAN_DESTROYED,	WALL_POINT },
		{ '=', 8,	CAN_DESTROYED,	WALL_POINT },
		{ 13, 12,	CANt_DESTROYED,	NO_POINT  },
		{ 'M', 12,  CAN_DESTROYED,  WALL_POINT}
	},
	Bomb_Nm		= {'@', 7,	BOMB_SHOW,	NO_POINT},
	Bomb_burst	= {'X', 4,	BOMB_BURST,	NO_POINT },
	Life		= { 3, 6,	CAN_KEEP,	ITEM_POINT },
	Potion		= { 'P', 100, CAN_KEEP,	ITEM_POINT},
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
	playerMe.Position = {2, 1 };
	playerMe.Attribute = 150;
	playerMe.Lenght = 3;
	playerMe.Height = 3;
	playerMe.SpeedX = 3;
	playerMe.SpeedY = 3;
	playerMe.Bomb.Amount = 5;
	playerMe.Bomb.Time = 30;
	playerMe.Bomb.PowerX = 3;
	playerMe.Bomb.PowerY = 3;

		playerBot[0].Position = { 44, 1 };
		//playerBot[1].Position = { 2, 37 };

		setupBot(&playerBot[0]);
		//setupBot(&playerBot[1]);

		playerBot[0].Attribute = 180;
		//playerBot[1].Attribute = 180;

	setupBomb(&playerMe);
	setMode();
	// 
	//while() // เลือก map
	setupMap(&nMap[0], 2);

	while (playStatus /*&& playerMe.Life >= 0*/) {
		// Input Keyboard & Mouse events
		int Forwalk = rand();
		moveControl(&playerMe, &nMap[0]);

			moveBot(&playerBot[0], &nMap[0]); // include dropBomb
			//moveBot(&playerBot[1], &nMap[0]);

		clearBuffer();

		changeStateMap(&nMap[0]);
		setOfBomb(&playerMe, &nMap[0]);
			setOfBot(&playerBot[0], &nMap[0]);
			//setOfBot(&playerBot[1], &nMap[0]);

		playerMove(&playerMe, &nMap[0]);

		checkBomb(&playerMe, &nMap[0]);
			checkBomb(&playerBot[0], &nMap[0]);

		displayBuffer(); 

		Summary(&playerMe, { MAP_WIDTH, 2 });
			Summary(&playerBot[0], { MAP_WIDTH, 12 });
			//Summary(&playerBot[1], { MAP_WIDTH, 18 });

		Sleep(150);
	}

	//clearBuffer();
	//displayBuffer();
	//gotoxy(0, 0);
	//printf_s("GAME OVER!!!")S;
	return 0;
}