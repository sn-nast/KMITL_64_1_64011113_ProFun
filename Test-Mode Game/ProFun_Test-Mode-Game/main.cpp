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
_Map Map[5];

_Object Wall_1, Wall_2, Obj_Potion;


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

	//Wall_1 = { '#', NORMAL_ATTIBUTE };
	//Obj_Potion = { '#', NORMAL_ATTIBUTE };


	setupBomb(&playerMe);
	setMode();

	while (playStatus) {
		// Input Keyboard & Mouse events
		//gotoxy(38, 100);
		//printf_s("(%d, %d)", playerMe.Position.X, playerMe.Position.Y);

		moveControl(&playerMe);
		clearBuffer();
		//planMap1();
		dropBomb(&playerMe);
		checkBomb(&playerMe);
		showBomb(&playerMe);
		playerMove(&playerMe);
		putBuffer(35, 100, playerMe.Position.X, NORMAL_ATTIBUTE);

		displayBuffer();

		Sleep(100);
	}
	return 0;
}