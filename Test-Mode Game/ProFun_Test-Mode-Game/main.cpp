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
	Space = { ' ', NORMAL_ATTIBUTE, MAP_SPACE},
	Wall_1 = { SYM_SHARP, 9, CAN_DESTROY },
	Wall_2 = { '|', 10, CANt_DESTROY },
	Bomb_Nm = {'@', 7, BOMB_SHOW},
	Bomb_burst = {'X', 4, BOMB_BURST},
	Life = { 3, 6, CAN_KEEP },
	Potion = { SYM_POTION, 11, CAN_KEEP }
;

int main() {
	srand(time(NULL));

	printf_s("\n");
	setConsole(SCREEN_WIDTH, SCREEN_HEIGHT);
	setCursor(0);

	// Setup 
	strcpy_s(playerMe.Format, "O");
	playerMe.Position = { 18, 14 };
	playerMe.Attribute = 5;
	playerMe.Lenght = strlen(playerMe.Format);
	playerMe.Bomb.Amount = 5;
	playerMe.Bomb.Time = 15;
	playerMe.SpeedX = 1;

	playerBot[0].Position = { 25, 14 };
	setupBot(&playerBot[0]);
	//
	//printf_s("%d", playerMe.Lenght);
	setupBomb(&playerMe);
	setMode();

	//while() // เลือก map
	setupMap(&nMap[0], 1);

	while (playStatus /*&& playerMe.Life >= 0*/) {
		// Input Keyboard & Mouse events
		int Forwalk = rand();
		moveControl(&playerMe, &nMap[0]);
		//moveControl(&playerBot[0], &nMap[0]);

		if (Forwalk % 2 == 0) { moveBot(&playerBot[0], &nMap[0]); }

		clearBuffer();

		changeStateMap(&nMap[0]);

		dropBomb(&playerMe, &nMap[0]);
		showBomb(&playerMe, &nMap[0]);
		checkBomb(&playerMe, &nMap[0]);

		playerMove(&playerMe, &nMap[0]);
		playerMove(&playerBot[0], &nMap[0]);

		displayBuffer(); 

		gotoxy(MAP_WIDTH + 10, 0);
		printf_s("HELLO");
		//Summary();
		Sleep(150);
	}

	//clearBuffer();
	displayBuffer();
	gotoxy(0, 0);
	printf_s("GAME OVER!!!");
	return 0;
}