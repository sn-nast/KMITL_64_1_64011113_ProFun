#include "StartAndSetup.h"
#include "Buffer.h"
#include "main.h"
#include "Bomb.h"
#include "Point.h"
#include "Bot.h"

bool programStatus = true;
bool playStatus = true;
bool homePageStatus = true;
bool inputPlayerName = false;
bool endGameStatus = false;
int mapSelected = 0;
unsigned int levelPlayer = 1;
const int amountMap = sizeof(playMap) / sizeof(playMap[0]);
unsigned int countWin = 0;
unsigned int countLost = 0;
Player playerMe;

void setAllScreen() {
	setConsole(SCREEN_WIDTH, SCREEN_HEIGHT);
	setCursor(0);
}

void setupPlayerToOrigin(Player* p) {
	// basic property
	p->Dir_atb = 4;
	p->Lenght = 3;
	p->Height = 3;
	p->SpeedX = p->Lenght;
	p->SpeedY = p->Height;
	p->Life = 1;
	p->Point = 0;
	p->Call = 0;
	setupBomb(p);
}

void setupAllPlayerToOrigin() {
	setupPlayerToOrigin(&playerMe);
	int amountBot = sizeof(playerBot) / sizeof(playerBot[0]);
	for (int n = 0; n < amountBot; n++) {
		setupPlayerToOrigin(&playerBot[n]);
	}
	setupPlayerMe();
	setupAllPlayerBot();
}

void setupPlayerMe() {
	setupBomb(&playerMe);
	strcpy_s(playerMe.Format, "P");
	playerMe.Position = { 2 ,1 };
	playerMe.StartPositon = playerMe.Position;
	playerMe.Attribute = 23;
	playerMe.Call = 10;
	summaryLastLine = 3;
}

void homePage() {
	int col = rand() % 14 + 1; 
	int nowSelected = 0;
	int charName = 0;
	char playerName[30];
	int sizeLenName = sizeof(playerName) / sizeof(playerName[0]);
	char gameTitle[][SCREEN_WIDTH] = {
		// colossal font (https://www.messletters.com/en/big-text/),
		{"                                                                                                                       "},
		{" 888888b.                                888																			 "},
		{" 888  \"88b                               888																			 "},
		{" 888  .88P                               888																			 "},
		{" 8888888K.     .d88b.    88888b.d88b.    88888b.     .d88b.    888d888    88888b.d88b.     8888b.    88888b.			 "},
		{" 888  \"Y88b   d88\"\"88b   888 \"888 \"88b   888 \"88b   d8P  Y8b   888P\"     888 \"888 \"88b       \"88b   888 \"88b"},
		{" 888    888   888  888   888  888  888   888  888   88888888   888       888  888  888   .d888888   888  888			 "},
		{" 888   d88P   Y88..88P   888  888  888   888 d88P   Y8b.       888       888  888  888   888  888   888  888			 "},
		{" 8888888P\"     \"Y88P\"    888  888  888   88888P\"     \"Y8888    888       888  888  888   \"Y888888   888  888	 "},
		{"                                                                                                                       "}

	};
	int heightTitle = sizeof(gameTitle) / sizeof(gameTitle[0]);
	char selectOption[][15] = {
		{"Your name"}, {"PLAY!!!"}, {"Select map"}, {"Exit"}
	};

	const int sizeSeOp = sizeof(selectOption) / sizeof(selectOption[0]);
	while (homePageStatus) {
		int lastLine = 0;
		if (inputPlayerName == false) {
			clearBuffer();
			displayBuffer();
		}
		setcolor(col, 0);
		for (int i = 0; i < heightTitle; i++) {
			for (int j = 0; j < SCREEN_WIDTH; j++) {
				gotoxy(j + 5, i + 5);
				printf("%c", gameTitle[i][j]);
				lastLine = i + 5;
			}
		}
		setcolor(15, 0);
		lastLine += 5;

		COORD posShowPoint = { SCREEN_WIDTH - 50, lastLine };
		showHighestPoint(posShowPoint);

		int textCommentLine = 30;
		if (inputPlayerName == true) {
			gotoxy(15, textCommentLine++);
			printf("Use [Up or Down arrow key]");
			gotoxy(15, textCommentLine++);
			printf("then press [Enter] to select option.");
			gotoxy(15, ++textCommentLine);
			printf("Press [Esc] to exit game.");
		}
		else {
			gotoxy(15, lastLine + 3);
			printf("Please use \"_\" or \"-\" instead of spaces.");
			gotoxy(15, lastLine + 6);
			printf("Enter your Name and press [Enter] to continue.");
			gotoxy(15, lastLine + 7);
			printf("Press [ESC] to clear your input.");
		}
		textCommentLine += 5;
		gotoxy(2, textCommentLine);
		printf("Developed by Natchanon Bunyachawaset (64011113)");

		if (inputPlayerName == false) {
			setMode(0);
			setCursor(1);
			strcpy(playerName, " ");
			gotoxy(15, lastLine);	
			printf("%-20s : ", "Enter your name");
			scanf("%25s", &playerName);
			strcpy(playerMe.Name, playerName);
			inputPlayerName = true;
			setCursor(0);
			clearBuffer();
			displayBuffer();
			setMode(1);
		}
		else {
			controlSelectInHomePage(sizeSeOp, &nowSelected);
			for (int n = 0; n < sizeSeOp; n++) {
				gotoxy(15, lastLine);
				printf("%-20s ", selectOption[n]);

				// Clear arrow
				gotoxy(12, lastLine);
				printf(" ");
				if (n == nowSelected) {
					gotoxy(12, lastLine);
					printf("%c", RIGHT_ARROW_1);
				}
				if (n == 0) {
					gotoxy(12 + strlen(selectOption[0]) + 8, lastLine);
					printf(": %s", playerMe.Name);

				}
				else if (n == 2) {
					gotoxy(12 + strlen(selectOption[2]) + 8, lastLine);
					if (mapSelected != amountMap) {
						printf("( Map %d  )", mapSelected + 1);
					}
					else { printf("( Random )"); }
				}
				lastLine += 2;
			}
		}
	}
	if (mapSelected == amountMap) {
		mapSelected = rand() % (3 + 1);
	}
	clearBuffer();
	displayBuffer();
	setMode(1);
}

void controlSelectInHomePage(int sizeOption, int* nowSelected) {
	GetNumberOfConsoleInputEvents(rHnd, &numEvents);
	if (numEvents != 0) {
		INPUT_RECORD* eventBuffer = new INPUT_RECORD[numEvents];
		ReadConsoleInput(rHnd, eventBuffer, numEvents, &numEventsRead);

		for (DWORD i = 0; i < numEventsRead; ++i) {
			if (eventBuffer[i].EventType == KEY_EVENT &&
				eventBuffer[i].Event.KeyEvent.bKeyDown == TRUE) {
				char KB_Char = eventBuffer[i].Event.KeyEvent.uChar.AsciiChar;
				WORD KB_keycode = eventBuffer[i].Event.KeyEvent.wVirtualKeyCode;

				if (inputPlayerName == true) {
					if (KB_keycode == VK_ESCAPE || (KB_keycode == VK_RETURN && *nowSelected == 3)) {
						clearBuffer();
						displayBuffer();
						//clearScreen();

						gotoxy(0, 0);
						printf("END!!");
						homePageStatus = false;
						playStatus = false;
						programStatus = false;
						return;
					}
					if (KB_keycode == VK_RETURN) {
						if (*nowSelected == 0) {
							homePageStatus = true;
							inputPlayerName = false;
						}
						else if (*nowSelected == 1) {
							homePageStatus = false;
							playStatus = true;
						}
						else if (*nowSelected == 2) {
							if (mapSelected == amountMap) {
								mapSelected = 0;
							}
							else { mapSelected++; }
						}
					}
					switch (KB_Char | KB_keycode) {
					case 's':
					case 'S':
					case VK_DOWN: {
						if (*nowSelected < sizeOption - 1) {
							(*nowSelected)++;
						}
						else { *nowSelected = sizeOption - 1; }
						break;
					}

					case 'w':
					case 'W':
					case VK_UP: {
						if (*nowSelected > 0) {
							(*nowSelected)--;
						}
						else { *nowSelected = 0; }
						break;
					}
					default: break;
					}
				}
			}
		}
		delete[] eventBuffer;
	}
}

void gamePlayPageAndGameCheck() {
	setcolor(15, 0);
	gotoxy(8, MAP_HEIGHT + 2);
	printf("Press [Esc] to return Home page");
	if (playerMe.Life == 0) {
		playStatus = false;
		endGameStatus = true;
		countLost++;
	}
	
	int countBotAlive = 0;
	for (int n = 0; n < amountBot; n++) {
		if (playerBot[n].Bot.Alive == true) { countBotAlive++; }
	}
	if (countBotAlive == 0) {
		playStatus = false;
		endGameStatus = true;
		winStatus = true;
		countWin++;
	}
}

void endGamePage() {
	setMode(1);
	char Text_gameOver[][SCREEN_WIDTH] = {
		{"                                                                                                           "},
		{"    .88888.  .d888888   8888ba.88ba   88888888b     .88888.  dP     dP  88888888b  888888ba     dP dP dP   "},
		{"   d8'   `88 d8'    88  88  `8b  `8b  88           d8'   `8b 88     88  88         88    `8b    88 88 88   "},
		{"   88        88aaaaa88  88   88   88  88aaaa       88     88 88    .8P  88aaaa     88aaaa8P'    88 88 88   "},
		{"   88   YP88 88     88  88   88   88  88           88     88 88    d8'  88         88   `8b.    dP dP dP   "},
		{"   Y8.   .88 88     88  88   88   88  88           Y8.   .8P 88.d8P     88         88     88               "},
		{"    `88888'  88     88  dP   dP   dP  88888888P     `8888P'  888888'    88888888P  dP     dP    oo oo oo   "},
		{"                                                                                                           "}
	};

	char Text_timeUp[][SCREEN_WIDTH] = {
		{"                                                                            "},
		{"  88888888888 d8b                       d8b            888     888          "},
		{"      888     Y8P                       88P            888     888          "},
		{"      888                               8P             888     888          "},
		{"      888     888 88888b.d88b.   .d88b. '  .d8888b     888     888 88888b.  "},
		{"      888     888 888 '888 '88b d8P  Y8b   88K         888     888 888 '88b "},
		{"      888     888 888  888  888 88888888   'Y8888b.    888     888 888  888 "},
		{"      888     888 888  888  888 Y8b.            X88    Y88b. .d88P 888 d88P "},
		{"      888     888 888  888  888  'Y8888     88888P'     'Y88888P'  88888P'  "},
		{"                                                                   888      "},
		{"                                                                   888      "},
		{"                                                                   888      "},
		{"                                                                            "}
	};

	char Text_Win[][SCREEN_WIDTH] = {
		{"                                                           "},
		{"   888       888   8888888   888b    888     888 888 888   "},
		{"   888   o   888     888     8888b   888     888 888 888   "},
		{"   888  d8b  888     888     88888b  888     888 888 888   "},
		{"   888 d888b 888     888     888Y88b 888     888 888 888   "},
		{"   888d88888b888     888     888 Y88b888     888 888 888   "},
		{"   88888P Y88888     888     888  Y88888     Y8P Y8P Y8P   "},
		{"   8888P   Y8888     888     888   Y8888      :   :   :    "},
		{"   888P     Y888   8888888   888    Y888     888 888 888   "},
		{"                                                           "}
	};

	int TextHeight = 0;	
	int lastLine = 0;
	int nowSelected = 1;
	clearBuffer();
	displayBuffer();
	while (endGameStatus) {
		char selectOption[][15] = {
			{"Your point"}, {"Play Again"}, {"Home"}, {"Exit"}
		};
		int sizeSeOp = sizeof(selectOption) / sizeof(selectOption[0]);

		if (playerMe.Life == 0) {
			TextHeight = sizeof(Text_gameOver) / sizeof(Text_gameOver[0]);
			for (int i = 0; i < TextHeight; i++) {
				for (int j = 0; j < SCREEN_WIDTH; j++) {
					setcolor(4, 4);
					gotoxy(j + 5, i + 8);
					if (Text_gameOver[i][j] == ' ') {
						setcolor(15, 0);
					}
					printf("%c", Text_gameOver[i][j]);
				}
				lastLine = i + 8;
			}
		}
		else if (timeUp == true) {
			TextHeight = sizeof(Text_timeUp) / sizeof(Text_timeUp[0]);
			for (int i = 0; i < TextHeight; i++) {
				for (int j = 0; j < SCREEN_WIDTH; j++) {
					setcolor(4, 4);
					gotoxy(j + 5, i + 8);
					if (Text_timeUp[i][j] == ' ') { setcolor(15, 0);}
					printf("%c", Text_timeUp[i][j]);
				}
				lastLine = i + 8;
			}
		}

		else if (winStatus == true) {
			TextHeight = sizeof(Text_Win) / sizeof(Text_Win[0]);
			for (int i = 0; i < TextHeight; i++) {
				for (int j = 0; j < SCREEN_WIDTH; j++) {
					setcolor(2, 2);
					gotoxy(j + 5, i + 8);
					if (Text_Win[i][j] == ' ') { setcolor(15, 0); }
					printf("%c", Text_Win[i][j]);
				}
				lastLine = i + 8;
			}
		}
		lastLine++;

		setcolor(15, 0);
		int textCommentLine = 30;
		gotoxy(15, textCommentLine++);
		printf("Use [Up or Down arrow key]");
		gotoxy(15, textCommentLine++);
		printf("then press [Enter] to select option.");
		gotoxy(15, ++textCommentLine);
		printf("Press [Esc] to exit game.");
		textCommentLine += 5;
		gotoxy(2, textCommentLine);
		printf("Developed by Natchanon Bunyachawaset (64011113)");

		for (int n = 0; n < sizeSeOp; n++) {
			gotoxy(15, lastLine);
			printf("%s", selectOption[n]);

			// Clear arrow
			gotoxy(12, lastLine);
			printf(" ");
			if (n == nowSelected) {
				gotoxy(12, lastLine);
				printf("%c", RIGHT_ARROW_1);
			}
			if (n == 0) {
				gotoxy(12 + strlen(selectOption[n]) + 8, lastLine);
				printf(": %d", playerMe.Point);
			}
			else if (n == 1) {
				gotoxy(12 + strlen(selectOption[n]) + 8, lastLine);
				printf("(Map : %d) \t[Level %d]", mapSelected + 1, levelPlayer);
			}
			lastLine += 2;
		}
		controlSelectInEndGame(sizeSeOp, &nowSelected);
	}
	timeUp = false;
	winStatus = false;
	clearBuffer();
	displayBuffer();
	setMode(1);
}

void controlSelectInEndGame(int sizeOption, int* nowSelected) {
	GetNumberOfConsoleInputEvents(rHnd, &numEvents);
	if (numEvents != 0) {
		INPUT_RECORD* eventBuffer = new INPUT_RECORD[numEvents];
		ReadConsoleInput(rHnd, eventBuffer, numEvents, &numEventsRead);
		for (DWORD i = 0; i < numEventsRead; ++i) {
			if (eventBuffer[i].EventType == KEY_EVENT &&
				eventBuffer[i].Event.KeyEvent.bKeyDown == TRUE) {
				char KB_Char = eventBuffer[i].Event.KeyEvent.uChar.AsciiChar;
				WORD KB_keycode = eventBuffer[i].Event.KeyEvent.wVirtualKeyCode;
					if (KB_keycode == VK_ESCAPE || (KB_keycode == VK_RETURN) && *nowSelected == 3) {
						clearBuffer();
						displayBuffer();
						gotoxy(0, 0);
						printf("END!!");
						endGameStatus = false;
						homePageStatus = false;
						playStatus = false;
						programStatus = false;
						return;
					}
					if (KB_keycode == VK_RETURN) {
						if (*nowSelected == 1) {
							endGameStatus = false;
							playStatus = true;
						}
						else if (*nowSelected == 2) {
							endGameStatus = false;
							homePageStatus = true;
						}
					}
					switch (KB_Char | KB_keycode) {
					case 's':
					case 'S':
					case VK_DOWN: {
						if (*nowSelected < sizeOption - 1) {
							(*nowSelected)++;
						}
						else { *nowSelected = sizeOption - 1; }
						break;
					}

					case 'w':
					case 'W':
					case VK_UP: {
						if (*nowSelected > 1) {
							(*nowSelected)--;
						}
						else { *nowSelected = 1; }
						break;
					}
					default: break;
					}
				}
		}
		delete[] eventBuffer;
	}
}

void changeLevelPlayer() {
	if (countWin < 1) {
		levelPlayer = 1;
	}
	else if (countWin > 1) {
		levelPlayer = 2;
	}
}