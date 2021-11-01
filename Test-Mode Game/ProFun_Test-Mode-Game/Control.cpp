#include"Control.h"
#include "main.h"
#include "Buffer.h"

void moveControl(Player* p, Map* m) {
	GetNumberOfConsoleInputEvents(rHnd, &numEvents);
	if (numEvents != 0) {
		INPUT_RECORD* eventBuffer = new INPUT_RECORD[numEvents];
		ReadConsoleInput(rHnd, eventBuffer, numEvents, &numEventsRead);

		for (DWORD i = 0; i < numEventsRead; ++i) {
			if (eventBuffer[i].EventType == KEY_EVENT &&
				eventBuffer[i].Event.KeyEvent.bKeyDown == TRUE) {
				char KB_Char = eventBuffer[i].Event.KeyEvent.uChar.AsciiChar;
				WORD KB_keycode = eventBuffer[i].Event.KeyEvent.wVirtualKeyCode;
				if (KB_keycode == VK_ESCAPE) { 
					clearBuffer();
					displayBuffer();
					gotoxy(0, 0);
					printf_s("END!!");
					playStatus = FALSE; }
				if (KB_keycode == VK_SPACE) {
					COORD pos = { p->Position.X , p->Position.Y };
					int size = p->Bomb.Amount;
					int i = 0;
					if (p->Bomb.Drop < size) {
						for (int c = 0; c < size; c++) {
							if (p->Bomb.State[c] == 2) { i++; }
						}
						if (m->State[pos.Y][pos.X] == Bomb_Nm.NormalState) {
							goto jump;
						}
						if (p->Bomb.Drop < size - i) { p->Bomb.Drop++; }
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
			else if (eventBuffer[i].EventType == MOUSE_EVENT) {
				//int M_posx = eventBuffer[i].Event.MouseEvent.dwMousePosition.X;
				//int M_posy = eventBuffer[i].Event.MouseEvent.dwMousePosition.Y;
				if (eventBuffer[i].Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED) {
					//printf("left click\n")
					;
				}
				else if (eventBuffer[i].Event.MouseEvent.dwButtonState & RIGHTMOST_BUTTON_PRESSED) {
					//printf("right click\n")
					;
				}
				else if (eventBuffer[i].Event.MouseEvent.dwEventFlags & MOUSE_MOVED) {
					;
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
				if (checkStateControl(*State) == 1) { check++; }
			}
			if (check == Len * Hei) { pos->X -= p->SpeedX; }
		}
	}
	else if (Direction == RIGHT) {
		for (int H = 0; H < Hei; H++) {
			for (int L = 0; L < Len; L++) {
				State = &m->State[pos->Y + H][pos->X + L + p->SpeedX];
				if (checkStateControl(*State) == 1) { check++; }
			}
			if (check == Len * Hei) { pos->X += p->SpeedX; }
		}
	}
	else if (Direction == DOWN) {
		for (int H = 0; H < Hei; H++) {
			for (int L = 0; L < Len; L++) {
				State = &m->State[pos->Y + H + p->SpeedY][pos->X + L];
				if (checkStateControl(*State) == 1) { check++; }
			}
		}
		if (check == Len * Hei) { pos->Y += p->SpeedY; }
	}
	else if (Direction == UP) {
		for (int H = 0; H < Hei; H++) {
			for (int L = 0; L < Len; L++) {
				State = &m->State[pos->Y - 1 - H][pos->X + L];
				if (checkStateControl(*State) == 1) { check++; }
			}
		}
		if (check == Len * Hei) { pos->Y -= p->SpeedY; }
	}
}

int checkStateControl(unsigned int St) {
	if (St == Space.NormalState ||
		St == Bomb_burst.NormalState ||
		St == CAN_KEEP)
		{ return 1; }
	else return 0;
}