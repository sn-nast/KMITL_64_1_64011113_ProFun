#include "Move.h"
#include "Buffer.h"
#include "main.h"

const int SCREEN_WIDTH = 80;
const int SCREEN_HEIGHT = 80;
const int NORMAL_ATTIBUTE = 7;

HANDLE wHnd = 0 ;
HANDLE rHnd = 0;
DWORD fdwMode = 0;

CHAR_INFO consoleBuffer[SCREEN_WIDTH * SCREEN_HEIGHT];
COORD bufferSize = { SCREEN_WIDTH,SCREEN_HEIGHT };
COORD characterPos = { 0, 0 };
SMALL_RECT windowSize = { 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1 };

bool playStatus;
Player playerMe, * P_playerMe, player2;

int main() {
	setCursor(0);
	setConsole(SCREEN_WIDTH, SCREEN_HEIGHT);
	strcpy_s(playerMe.format, "[O]");
	playerMe.position = { 5, 5 };
	playerMe.attribute = 7;
	playerMe.lenght = strlen(playerMe.format);


	DWORD numEvents = 0;
	DWORD numEventsRead = 0;
	setMode();
	playStatus = TRUE;
	while (playStatus) {
		// Input Keyboard & Mouse events
		GetNumberOfConsoleInputEvents(rHnd, &numEvents);
		if (numEvents != 0) {
			INPUT_RECORD* eventBuffer = new INPUT_RECORD[numEvents];
			ReadConsoleInput(rHnd, eventBuffer, numEvents, &numEventsRead);

			for (DWORD i = 0; i < numEventsRead; ++i) {
				if (eventBuffer[i].EventType == KEY_EVENT &&
					 eventBuffer[i].Event.KeyEvent.bKeyDown == true){
					char KB_Char = eventBuffer[i].Event.KeyEvent.uChar.AsciiChar;
					WORD KB_keycode = eventBuffer[i].Event.KeyEvent.wVirtualKeyCode;
					if (KB_Char == VK_ESCAPE) {
						playStatus = FALSE;
					}
					playerMe.last_position.X = playerMe.position.X;
					playerMe.last_position.Y = playerMe.position.Y;
					switch (KB_Char | KB_keycode) {
						case 'a'		: {playerMe.position.X--; break; }
						case 'A'		: {playerMe.position.X--; break; }
						case VK_LEFT	: {playerMe.position.X--; break; }
						case 'd'		: {playerMe.position.X++; break; }
						case 'D'		: {playerMe.position.X++; break; }
						case VK_RIGHT	: {playerMe.position.X++; break; }
						case 's'		: {playerMe.position.Y++; break; }
						case 'S'		: {playerMe.position.Y++; break; }
						case VK_DOWN	: {playerMe.position.Y++; break; }
						case 'w'		: {playerMe.position.Y--; break; }
						case 'W'		: {playerMe.position.Y--; break; }
						case VK_UP		: {playerMe.position.Y--; break; }
					default: break;
					}
				}
				else if (eventBuffer[i].EventType == MOUSE_EVENT) {
					int M_posx = eventBuffer[i].Event.MouseEvent.dwMousePosition.X;
					int M_posy = eventBuffer[i].Event.MouseEvent.dwMousePosition.Y;
					if (eventBuffer[i].Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED) {
						printf("left click\n");;
					}
					else if (eventBuffer[i].Event.MouseEvent.dwButtonState & RIGHTMOST_BUTTON_PRESSED) {
						printf("right click\n");;
					}
					else if (eventBuffer[i].Event.MouseEvent.dwEventFlags & MOUSE_MOVED) {
						;
					}
				}
			}
			delete[] eventBuffer;
		}
		clearBuffer();
		playerMove(playerMe);
		displayBuffer();
		Sleep(100);
	}
	return 0;
}
