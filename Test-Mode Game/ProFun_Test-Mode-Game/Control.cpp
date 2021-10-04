#include"Control.h"
#include "main.h"

void moveControl(Player *P_struct) {
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
					P_struct->Bomb.Drop++; 
				}
				P_struct->Last_position.X = P_struct->Position.X;
				P_struct->Last_position.Y = P_struct->Position.Y;
				switch (KB_Char | KB_keycode) {
				case 'a'		:{ P_struct->Position.X--; break; }
				case 'A'		:{ P_struct->Position.X--; break; }
				case VK_LEFT	: { P_struct->Position.X--; break; }
				case 'd'		: { P_struct->Position.X++; break; }
				case 'D'		: { P_struct->Position.X++; break; }
				case VK_RIGHT	: { P_struct->Position.X++; break; }
				case 's'		: { P_struct->Position.Y++; break; }
				case 'S'		: { P_struct->Position.Y++; break; }
				case VK_DOWN	: { P_struct->Position.Y++; break; }
				case 'w'		: { P_struct->Position.Y--; break; }
				case 'W'		: { P_struct->Position.Y--; break; }
				case VK_UP		: { P_struct->Position.Y--; break; }
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