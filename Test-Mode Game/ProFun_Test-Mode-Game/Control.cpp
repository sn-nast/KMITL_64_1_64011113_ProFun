#include"Control.h"
#include "main.h"

void moveControl(Player* p) {
	GetNumberOfConsoleInputEvents(rHnd, &numEvents);
	if (numEvents != 0) {
		INPUT_RECORD* eventBuffer = new INPUT_RECORD[numEvents];
		ReadConsoleInput(rHnd, eventBuffer, numEvents, &numEventsRead);

		for (DWORD i = 0; i < numEventsRead; ++i) {
			if (eventBuffer[i].EventType == KEY_EVENT &&
				eventBuffer[i].Event.KeyEvent.bKeyDown == true) {
				char KB_Char = eventBuffer[i].Event.KeyEvent.uChar.AsciiChar;
				WORD KB_keycode = eventBuffer[i].Event.KeyEvent.wVirtualKeyCode;
				if (KB_keycode == VK_ESCAPE) { playStatus = FALSE; }
				if (KB_keycode == VK_SPACE) {
					int size = p->Bomb.Amount;
					int i = 0;
					if (p->Bomb.Drop < size) {
						for (int c = 0; c < size; c++) {
							if (p->Bomb.State[c] == 2) { i++; }
							if ((p->Direction.X == p->Bomb.Position[c].X
								&& p->Direction.Y == p->Bomb.Position[c].Y)) {
								goto jump;
							}
						}
						if (p->Bomb.Drop < size - i) { p->Bomb.Drop++; }
					}
				}
			jump:
				p->Last_position.X = p->Position.X;
				p->Last_position.Y = p->Position.Y;
				switch (KB_Char | KB_keycode) {
				case 'a': { p->Position.X--; break; }
				case 'A': { p->Position.X--; break; }
				case VK_LEFT: { p->Position.X--; break; }
				case 'd': { p->Position.X++; break; }
				case 'D': { p->Position.X++; break; }
				case VK_RIGHT: { p->Position.X++; break; }
				case 's': { p->Position.Y++; break; }
				case 'S': { p->Position.Y++; break; }
				case VK_DOWN: { p->Position.Y++; break; }
				case 'w': { p->Position.Y--; break; }
				case 'W': { p->Position.Y--; break; }
				case VK_UP: { p->Position.Y--; break; }
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