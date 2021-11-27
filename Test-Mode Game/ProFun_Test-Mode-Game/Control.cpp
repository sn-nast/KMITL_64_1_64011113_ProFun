#include"Control.h"
#include "main.h"
#include "Buffer.h"

HANDLE wHnd;
HANDLE rHnd;
DWORD fdwMode;
DWORD numEvents = 0;
DWORD numEventsRead = 0;

void moveControl(Player* p, Map* m) {
	GetNumberOfConsoleInputEvents(rHnd, &numEvents);
	if (numEvents != 0) {
		INPUT_RECORD* eventBuffer = new INPUT_RECORD[numEvents];
		ReadConsoleInput(rHnd, eventBuffer, numEvents, &numEventsRead);

		for (DWORD i = 0; i < 2; ++i) {
			if (eventBuffer[i].EventType == KEY_EVENT &&
				eventBuffer[i].Event.KeyEvent.bKeyDown == TRUE) {
				char KB_Char = eventBuffer[i].Event.KeyEvent.uChar.AsciiChar;
				WORD KB_keycode = eventBuffer[i].Event.KeyEvent.wVirtualKeyCode;
				if (KB_keycode == VK_ESCAPE) { 
					clearScreen();
					clearBuffer();
					displayBuffer();
					gotoxy(0, 0);
					playStatus = false; 
					homePageStatus = true;
					endGameStatus = false;
				}
				if (KB_keycode == VK_SPACE) {
					COORD pos = { p->Position.X , p->Position.Y };
					int size = p->Bomb.Amount;
					int i = 0;
					if (p->Bomb.CountBombDropNow < size) {
						for (int c = 0; c < size; c++) {
							if (p->Bomb.State[c] == BOMB_COUNTING) { i++; }
						}
						if (m->State[pos.Y][pos.X] == Bomb_Nm.NormalState) {
							goto jump;
						}
						if (p->Bomb.NewDrop < size - i) { 
							p->Bomb.NewDrop++; 
						}
					}
				}
			jump:
				p->Last_Position.X = p->Position.X;
				p->Last_Position.Y = p->Position.Y;
				COORD* pos = &p->Position;

				switch (KB_Char | KB_keycode) {
					case 'a':		{ checkControl(LEFT, p, m); break; }
					case 'A':		{ checkControl(LEFT, p, m); break; }
					case VK_LEFT:	{ checkControl(LEFT, p, m); break; }
					case 'd':		{ checkControl(RIGHT, p, m); break; }
					case 'D':		{ checkControl(RIGHT, p, m); break; }
					case VK_RIGHT:	{ checkControl(RIGHT, p, m); break; }
					case 's':		{ checkControl(DOWN, p, m); break; }
					case 'S':		{ checkControl(DOWN, p, m); break; }
					case VK_DOWN:	{ checkControl(DOWN, p, m); break; }
					case 'w':		{ checkControl(UP, p, m); break; }
					case 'W':		{ checkControl(UP, p, m); break; }
					case VK_UP:		{ checkControl(UP, p, m); break; }
				default: break;
				}
			}
		}
		delete[] eventBuffer;
	}
}

void checkControl(int Direction, Player* p, Map* m) {
	COORD* pos = &p->Position;
	p->Last_Position.X = pos->X;
	p->Last_Position.Y = pos->Y;
	unsigned int* State;
	int Len = p->Lenght;
	int Hei = p->Height;
	int check = 0;
	if (Direction == LEFT) {
		for (int H = 0; H < Hei; H++) {
			for (int L = 0; L < Len; L++) {
				State = &m->State[pos->Y + H][pos->X - 1 - L ];
				if (checkStateControl(p, *State) == 1) { check++; }
			}
			if (check == Len * Hei) { pos->X -= p->SpeedX; }
		}
	}
	else if (Direction == RIGHT) {
		for (int H = 0; H < Hei; H++) {
			for (int L = 0; L < Len; L++) {
				State = &m->State[pos->Y + H][pos->X + L + p->SpeedX];
				if (checkStateControl(p, *State) == 1) { check++; }
			}
			if (check == Len * Hei) { pos->X += p->SpeedX; }
		}
	}
	else if (Direction == DOWN) {
		for (int H = 0; H < Hei; H++) {
			for (int L = 0; L < Len; L++) {
				State = &m->State[pos->Y + H + p->SpeedY][pos->X + L];
				if (checkStateControl(p, *State) == 1) { check++; }
			}
		}
		if (check == Len * Hei) { pos->Y += p->SpeedY; }
	}
	else if (Direction == UP) {
		for (int H = 0; H < Hei; H++) {
			for (int L = 0; L < Len; L++) {
				State = &m->State[pos->Y - 1 - H][pos->X + L];
				if (checkStateControl(p, *State) == 1) { check++; }
			}
		}
		if (check == Len * Hei) { pos->Y -= p->SpeedY; }
	}
}

int checkStateControl(Player*p, unsigned int St) {
	int n = 0;
	if (p->Call == playerMe.Call) {
		if (St == Space.NormalState ||
			St == Bomb_burst.NormalState ||
			St == CAN_KEEP) {
			n = 1;
		}
	}
	else if (levelPlayer == 1) {
		unsigned int timeNow = (playMap[mapSelected].GameTime_Minute * 60) + playMap[mapSelected].GameTime_Second;
		int randToKeepObect = rand() % 10;
		if (randToKeepObect < 8 || timeNow > 4 * 60) {
			if (St == Space.NormalState ||
				St == Bomb_burst.NormalState ||
				St == CAN_KEEP) {
				n = 1;
			}
		}
		else {
			if (St == Space.NormalState ||
				St == Bomb_burst.NormalState) {
				n = 1;
			}
		}
	}
	else if (levelPlayer == 2) {
		if (St == Space.NormalState ||
			St == Bomb_burst.NormalState ||
			St == CAN_KEEP) {
			n = 1;
		}
	}
	else { n = 0; }
	return n;
}
//int checkStateControl(Player* p, unsigned int St) {
//	int n = 0;
//	if (St == Space.NormalState ||
//		St == Bomb_burst.NormalState ||
//		St == CAN_KEEP) {
//		n = 1;
//	}
//	else { n = 0; }
//	return n;
//}