#include <windows.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#define scount 50
#define screen_x 80
#define screen_y 25

HANDLE wHnd;
HANDLE rHnd;
DWORD fdwMode;
CHAR_INFO consoleBuffer[screen_x * screen_y];
COORD bufferSize = { screen_x,screen_y };
COORD characterPos = { 0, 0 };
SMALL_RECT windowSize = { 0, 0, screen_x - 1, screen_y - 1 };
COORD star[scount];
int starColor = 6;

COORD ship;
const char myShip[6] = "<-0->";
int shipColor = 2;
int myHP = 10;

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
	consoleBuffer[x + ( screen_x * y )].Char.AsciiChar = ch;
	consoleBuffer[x + ( screen_x * y )].Attributes = atb;
}
void fill_buffer_to_console(){
	WriteConsoleOutputA(wHnd, consoleBuffer, bufferSize, characterPos, &windowSize);
} 
void clear_buffer() {
	for (int y = 0; y < screen_y; ++y) {
		for (int x = 0; x < screen_x; ++x) {fill_data_to_buffer(x, y, ' ', 7);}
	}
}

void init_star() {
	for (int i = 0; i < scount; i++) {
		star[i] = { short(rand() % screen_x + 1), short(rand() % screen_y + 1) };
		fill_data_to_buffer(star[i].X , star[i].Y, '*', starColor);
	}
}
void fill_star_to_buffer() {
	for (int i = 0; i < scount; i++) {
		fill_data_to_buffer(star[i].X, star[i].Y, '*', starColor);
	}
}
void star_fall() {
	int i;
	for (i = 0; i < scount; i++) {
		if (star[i].Y >= screen_y - 1) {
			star[i] = { short(rand() % screen_x),1 };
		}
		else {
			star[i].Y++;
			if (ship.Y == star[i].Y && ship.X <= star[i].X && 
				ship.X + unsigned(strlen(myShip)) >= unsigned(star[i].X)) {
				star[i] = { short(rand() % screen_x + 1), 1 };
				myHP--;
			}
		}
		fill_data_to_buffer(star[i].X, star[i].Y, '*', starColor);
	}
}
//type 0 = delete, 1 = draw
void draw_ship(int ship_x, int ship_y, int type) {
	while (shipColor == starColor || (type == 1 && (shipColor > 15 || shipColor == 0))) { shipColor = rand() % 256; }
	for (unsigned int i = 0; i < unsigned(strlen(myShip)); i++) {
		if (type == 1)		{ fill_data_to_buffer(ship_x + i, ship_y, myShip[i], shipColor); }
		else if (type == 0) { fill_data_to_buffer(ship_x + i, ship_y, ' ', 0);}
	}
}

int main() {
	srand(time_t(NULL));
	setConsole(screen_x, screen_y);
	init_star();
	bool play = true ;
	DWORD numEvents = 0;
	DWORD numEventsRead = 0;
	setConsole(screen_x, screen_y);
	setMode();
	while (play && myHP > 0) {
		GetNumberOfConsoleInputEvents(rHnd, &numEvents);
		if (numEvents != 0) {
			INPUT_RECORD* eventBuffer = new INPUT_RECORD[numEvents];
			ReadConsoleInput(rHnd, eventBuffer, numEvents, &numEventsRead);
			for (DWORD i = 0; i < numEventsRead; ++i) {
				if (eventBuffer[i].EventType == KEY_EVENT &&
					eventBuffer[i].Event.KeyEvent.bKeyDown == true) {
					if (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE) {
						play = false;
					}
					char keyPressed = eventBuffer[i].Event.KeyEvent.uChar.AsciiChar;
					if (keyPressed == 'c'){
						shipColor = rand() % 256;
						draw_ship(ship.X, ship.Y, 1);
					}
				}
				else if (eventBuffer[i].EventType == MOUSE_EVENT) {
					short posx = eventBuffer[i].Event.MouseEvent.dwMousePosition.X;
					short posy = eventBuffer[i].Event.MouseEvent.dwMousePosition.Y;
					if (eventBuffer[i].Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED) {
						shipColor = rand() % 256;
						draw_ship(ship.X, ship.Y, 1);
					}
					else if (eventBuffer[i].Event.MouseEvent.dwEventFlags & MOUSE_MOVED) {
						draw_ship(ship.X, ship.Y, 0);
						ship = { posx, posy };
					}
				}
			}
			delete[] eventBuffer;
		}
		star_fall();
		clear_buffer();
		fill_star_to_buffer();
		draw_ship(ship.X, ship.Y, 1);
		fill_buffer_to_console();
		Sleep(100);
	}
	return 0;
}