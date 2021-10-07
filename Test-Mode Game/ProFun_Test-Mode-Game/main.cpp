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
	Space = { ' ', NORMAL_ATTIBUTE },
	Wall_1 = { SYM_SHARP, 9 },
	Wall_2 = { '|', 10 },
	Potion = { SYM_POTION, 9 }
;
extern char m;
int main() {
	srand(time_t(NULL));
	setConsole(SCREEN_WIDTH, SCREEN_HEIGHT);
	setCursor(0);
	strcpy_s(playerMe.Format, "[O]");

	// Setup 
	playerMe.Position = { 5, 5 };
	playerMe.Attribute = 7;
	playerMe.Lenght = strlen(playerMe.Format);
	playerMe.Bomb.Amount = 5;
	playerMe.Bomb.Time = 30;

	//printf_s("%d", playerMe.Lenght);
	setupBomb(&playerMe);
	setMode();

	while (playStatus) {
		// Input Keyboard & Mouse events
		moveControl(&playerMe, &nMap[0]);
		clearBuffer();

		setupMap(&nMap[0], 1);
		dropBomb(&playerMe, &nMap[0]);
		checkBomb(&playerMe, &nMap[0]);
		showBomb(&playerMe);
		playerMove(&playerMe);
		putBuffer(35, 100, (char)playerMe.Position.X, NORMAL_ATTIBUTE);

		displayBuffer();

		Sleep(150);
	}
	return 0;
}