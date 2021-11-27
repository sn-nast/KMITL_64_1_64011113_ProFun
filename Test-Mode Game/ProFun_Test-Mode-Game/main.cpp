#include "main.h"
#include "Move.h"
#include "Buffer.h"
#include "Control.h"
#include "Bomb.h"
#include "Map.h" 
#include "Object.h"
#include "Bot.h"
#include "Point.h"
#include "StartAndSetup.h"

int main() {
	srand(time(NULL));

	// Setup 
	setAllScreen();
	levelPlayer = 1;

	// Read highest points
	readPoint();

	mapSelected = 2;
	while (programStatus) {
		//homePage();
		setMode(1);
		setupAllPlayerToOrigin();

		setupMap(&playMap[mapSelected], mapSelected + 1);
		Map* m = &playMap[mapSelected];

		while (playStatus) {
			moveControl(&playerMe, m);
				moveAllBot(m); 
				dropBombAllBot(m);
			clearBuffer();

			changeStateMap(m);
			setOfBomb(&playerMe, m);
				setOfAllBot(m);

			playerMove(&playerMe, m);

			checkBomb(&playerMe, m);
				checkBombAllBot(m);

			displayBuffer();
			summary(&playerMe, { MAP_WIDTH + 3, summaryLastLine });
			summaryAllBot();

			gamePlayPageAndGameCheck();

			countDownGameTime(m);
			countDownObjectAllPlayer();

			Sleep(150);
		}
		recordPoint(&playerMe);
		endGamePage();
		changeLevelPlayer();
		clearBuffer();
		displayBuffer();
	}
	return 0;
}