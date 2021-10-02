#include<Windows.h>
#include<time.h>

HANDLE rHnd;
HANDLE wHnd;
DWORD fdwMode;
bool playStatus;
DWORD numEvents = 0;
DWORD numEventsRead = 0;
INPUT_RECORD* eventBuffer = new INPUT_RECORD[numEvents];

void KB_Expression() {
	for (DWORD i = 0; i < numEventsRead; ++i){
	if (eventBuffer[i].EventType == KEY_EVENT &&
		eventBuffer[i].Event.KeyEvent.bKeyDown == true) {
		if (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE) {
			playStatus = false;
		}
		char keyPressed = eventBuffer[i].Event.KeyEvent.uChar.AsciiChar;
		if (keyPressed == 'c') {
		}
	}

	//while (playStatus) {
		//GetNumberOfConsoleInputEvents(rHnd, &numEvents);
		if (numEvents != 0) {
			ReadConsoleInput(rHnd, eventBuffer, numEvents, &numEventsRead);
			for (DWORD i = 0; i < numEventsRead; ++i) {
				if (eventBuffer[i].EventType == KEY_EVENT &&
					eventBuffer[i].Event.KeyEvent.bKeyDown == true) {
					if (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE) {
						playStatus = false;
					}
					char keyPressed = eventBuffer[i].Event.KeyEvent.uChar.AsciiChar;
					if (keyPressed == 'c') {
					}
				}
				else if (eventBuffer[i].EventType == MOUSE_EVENT) {
					short posx = eventBuffer[i].Event.MouseEvent.dwMousePosition.X;
					short posy = eventBuffer[i].Event.MouseEvent.dwMousePosition.Y;
					if (eventBuffer[i].Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED) {

					}
					else if (eventBuffer[i].Event.MouseEvent.dwEventFlags & MOUSE_MOVED) {

					}
				}
			}
			delete[] eventBuffer;
		}
	//}
}