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
				eventBuffer[i].Event.KeyEvent.bKeyDown == true) {
				char KB_Char = eventBuffer[i].Event.KeyEvent.uChar.AsciiChar;
				WORD KB_keycode = eventBuffer[i].Event.KeyEvent.wVirtualKeyCode;
				if (KB_keycode == VK_ESCAPE) { 
					clearBuffer();
					displayBuffer();
					gotoxy(0, 0);
					printf_s("END!!");
					playStatus = FALSE; }
				if (KB_keycode == VK_SPACE) {
					int size = p->Bomb.Amount;
					int i = 0;
					if (p->Bomb.Drop < size) {
						for (int c = 0; c < size; c++) {
							if (p->Bomb.State[c] == 2) { i++; }
							if ((p->Position.X == p->Bomb.Position[c].X
								&& p->Position.Y == p->Bomb.Position[c].Y)) {
								goto jump;
							}
						}
						if (p->Bomb.Drop < size - i) { p->Bomb.Drop++; }
					}
				}
			jump:
				p->Last_position.X = p->Position.X;
				p->Last_position.Y = p->Position.Y;
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
	int Len = p->Lenght;
	if (Direction == LEFT) {
		if (m->State[pos->Y][ pos->X - 1] == MAP_SPACE) {
			pos->X -= p->SpeedX;
		}
	}
	else if (Direction == RIGHT) {
		if (m->State[pos->Y][pos->X + Len + p->SpeedX - 1] == MAP_SPACE) {
			pos->X += p->SpeedX;
		}
	}
	else if (Direction == DOWN) {
		int c = 0;
		for (int i = 0; i < Len; i++) {
			if (m->State[pos->Y + p->SpeedY][pos->X + i] == MAP_SPACE) { c++; }
		}
		if (c == Len) { pos->Y += p->SpeedY; }
	}
	else if (Direction == UP) {
		int c = 0;
		for (int i = 0; i < Len; i++) {
			if (m->State[pos->Y - p->SpeedY][pos->X + i] == MAP_SPACE) { c++; }
		}
		if (c == Len) { pos->Y -= p->SpeedY; }
	}
}