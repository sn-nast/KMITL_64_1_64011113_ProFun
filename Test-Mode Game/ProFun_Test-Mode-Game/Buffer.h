#include<Windows.h>
#define screen_x 80
#define screen_y 25

HANDLE wHnd;
HANDLE rHnd;
DWORD fdwMode;
CHAR_INFO consoleBuffer[screen_x * screen_y];
COORD bufferSize = { screen_x,screen_y };
COORD characterPos = { 0, 0 };
SMALL_RECT windowSize = { 0, 0, screen_x - 1, screen_y - 1 };

int setConsole(int x, int y) {
	wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleWindowInfo(wHnd, TRUE, &windowSize);
	SetConsoleScreenBufferSize(wHnd, bufferSize);
	return 0;
}
int setMode() {
	rHnd = GetStdHandle(STD_INPUT_HANDLE);
	fdwMode = ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
	SetConsoleMode(rHnd, fdwMode);
	return 0;
}

void fill_data_to_buffer(int x, int y, char ch, int atb) {
	consoleBuffer[x + (screen_x * y)].Char.AsciiChar = ch;
	consoleBuffer[x + (screen_x * y)].Attributes = atb;
}
void fill_buffer_to_console() {
	WriteConsoleOutputA(wHnd, consoleBuffer, bufferSize, characterPos, &windowSize);
}