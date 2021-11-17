#include"Buffer.h"
#include"main.h"

CHAR_INFO consoleBuffer[SCREEN_WIDTH * SCREEN_HEIGHT];
COORD bufferSize = { SCREEN_WIDTH, SCREEN_HEIGHT };
COORD characterPos = { 0, 0 };
SMALL_RECT windowSize = { 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1 };

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

void putBuffer(int x, int y, char ch, int atb) {
	consoleBuffer[x + (SCREEN_WIDTH * y)].Char.AsciiChar = ch;
	consoleBuffer[x + (SCREEN_WIDTH * y)].Attributes = atb;
}

void displayBuffer() {
	WriteConsoleOutputA(wHnd, consoleBuffer, bufferSize, characterPos, &windowSize);
}

void clearBuffer() {
	for (int y = 0; y < SCREEN_HEIGHT; ++y) {
		for (int x = 0; x < SCREEN_WIDTH; ++x) { putBuffer(x, y, ' ', NORMAL_ATTIBUTE); }
	}
}

void setCursor(bool visible) {
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console, &lpCursor);
}

void gotoxy(int x, int y) {
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void setcolor(int fg, int bg) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, bg * 16 + fg);
}

char cursor(int x, int y) {
	HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);
	char buf[2]; COORD c = { x,y }; DWORD num_read;
	if (!ReadConsoleOutputCharacter(hStd, (LPTSTR)buf, 1, c, (LPDWORD)&num_read))
		return '\0';
	else
		return buf[0];
}

char cursorBuffer(COORD pos) {
	return consoleBuffer[pos.X + (SCREEN_WIDTH * pos.Y)].Char.AsciiChar;
}

void convertToChar(int n, char* keepArray) {
	int temp, digit = 0;
	temp = n;
	while (temp != 0) { 
		temp /= 10;
		digit++;
	}
	temp = n;
	for (int i = digit - 1; i >= 0; i--) {
		int inDigit = temp % 10;
		temp /= 10;
		keepArray[i] = (char)inDigit + '0';
	}
	keepArray[digit] = '\0';
}

void printBuffer(COORD pos, char* text) {
	for (int n = 0; n < strlen(text); n++) {
		putBuffer(pos.X + n, pos.Y, *(text + n), NORMAL_ATTIBUTE);
	}
}

void printBuffer(COORD pos, int n) {
	char intToChar[10];
	convertToChar(n, intToChar);
	for (int i = 0; i < strlen(intToChar); i++) {
		putBuffer(pos.X + i, pos.Y + 1, intToChar[i], NORMAL_ATTIBUTE);
	}
}