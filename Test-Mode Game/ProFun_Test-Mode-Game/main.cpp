#include "main.h"
#include "Move.h"
#include "Buffer.h"
#include "Control.h"
#include "Bomb.h"
#include "Map.h" 

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

Player playerMe, * P_playerMe, Newplay;
Map nMap[5];

_Object
	Space = { ' ', NORMAL_ATTIBUTE, 0 },
	Wall_1 = { SYM_SHARP, 9, 1 },
	Wall_2 = { '|', 10, 20 },
	Potion = { SYM_POTION, 9, 5 },
	Bomb_burst = {'X', 4, 10}
;
extern char m;
int main() {
	srand(time_t(NULL));
	setConsole(SCREEN_WIDTH, SCREEN_HEIGHT);
	setCursor(0);
	strcpy_s(playerMe.Format, "[O]");

	// Setup 
	playerMe.Position = { 18, 14 };
	playerMe.Attribute = 7;
	playerMe.Lenght = strlen(playerMe.Format);
	playerMe.Bomb.Amount = 5;
	playerMe.Bomb.Time = 10;
	playerMe.SpeedX = 1;

	//printf_s("%d", playerMe.Lenght);
	setupBomb(&playerMe);
	setMode();

	//while() // เลือก map
	setupMap(&nMap[0], 1);

	while (playStatus) {
		// Input Keyboard & Mouse events
		moveControl(&playerMe, &nMap[0]);
		clearBuffer();

		changeStateMap(&nMap[0]);
		dropBomb(&playerMe, &nMap[0]);
		checkBomb(&playerMe, &nMap[0]);
		showBomb(&playerMe);
		playerMove(&playerMe);

		displayBuffer();

		gotoxy(MAP_WIDTH + 10, 0);
		printf_s("HELLO");
		Sleep(150);
	}
	return 0;
}