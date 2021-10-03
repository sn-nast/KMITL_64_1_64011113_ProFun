#include "Move.h"
#include "Buffer.h"
#include "main.h"

const int SCREEN_WIDTH = 80;
const int SCREEN_HEIGHT = 80;

HANDLE wHnd;
HANDLE rHnd;
DWORD fdwMode;

CHAR_INFO consoleBuffer[SCREEN_WIDTH * SCREEN_HEIGHT];
COORD bufferSize = { SCREEN_WIDTH,SCREEN_HEIGHT };
COORD characterPos = { 0, 0 };
SMALL_RECT windowSize = { 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1 };

bool playStatus;
DWORD numEvents = 0;
DWORD numEventsRead = 0;
INPUT_RECORD* eventBuffer = new INPUT_RECORD[numEvents];

Player playerMe, player2;

int main() {
	setCursor(0);
	setConsole(SCREEN_WIDTH, SCREEN_HEIGHT);
	strcpy_s(playerMe.format, "[O]");
	playerMe.position = { 5, 5 };
	strcpy_s(player2.format, "[O-O]");
	playerMe.attribute = 7;

	printf("%s", playerMe.format);
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
					if (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE) {
						playStatus = FALSE;
					}
					switch (eventBuffer[i].Event.KeyEvent.uChar.AsciiChar) {
					case 'a': {playerMe.position.X--;	break; }
					case 'A': {playerMe.position.X--;	break; }
					case 'd': {playerMe.position.X++;	break; }
					case 'D': {playerMe.position.X++;	break; }
					case 's': {playerMe.position.Y++;	break; }
					case 'S': {playerMe.position.Y++;	break; }
					case 'w': {playerMe.position.Y--;	break; }
					case 'W': {playerMe.position.Y--;	break; }
					default: break;
					}
				}
				else if (eventBuffer[i].EventType == MOUSE_EVENT) {
					int M_posx = eventBuffer[i].Event.MouseEvent.dwMousePosition.X;
					int M_posy = eventBuffer[i].Event.MouseEvent.dwMousePosition.Y;
					if (eventBuffer[i].Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED) {
						;
					}
					else if (eventBuffer[i].Event.MouseEvent.dwButtonState & RIGHTMOST_BUTTON_PRESSED) {
						;
					}
					else if (eventBuffer[i].Event.MouseEvent.dwEventFlags & MOUSE_MOVED) {
						;
					}
				}
			}
			delete[] eventBuffer;
		}

		movePlayer({ playerMe.position.X, playerMe.position.Y }, playerMe.format, playerMe.attribute);

		Display();
		Sleep(100);
	}
	return 0;
}
