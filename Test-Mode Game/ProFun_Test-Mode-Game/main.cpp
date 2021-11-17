#include "main.h"
#include "Move.h"
#include "Buffer.h"
#include "Control.h"
#include "Bomb.h"
#include "Map.h" 
#include "Object.h"
#include "Bot.h"
#include "Point.h"

bool playStatus = true;
Player playerMe;/*, playerBot[3];*/

int main() {
	srand(time(NULL));
	setConsole(SCREEN_WIDTH, SCREEN_HEIGHT);
	setCursor(0);

	// Read highest points
	readPoint();

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
	playerMe.Point = 60000000;

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
	//showHighestPoint();

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