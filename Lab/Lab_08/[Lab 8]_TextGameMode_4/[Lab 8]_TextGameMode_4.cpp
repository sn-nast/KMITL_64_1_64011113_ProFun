#include <windows.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#define scount 10
#define screen_x 80
#define screen_y 25

HANDLE wHnd;
CHAR_INFO consoleBuffer[screen_x * screen_y];
COORD bufferSize = { screen_x,screen_y };
COORD characterPos = { 0, 0 };
SMALL_RECT windowSize = { 0, 0, screen_x - 1, screen_y - 1 };
COORD star[scount];

COORD ship;
const char myShip[6] = "<-->";
int shipColor = 2;

HANDLE rHnd;
DWORD fdwMode;
DWORD numEvents = 0;
DWORD numEventsRead = 0;


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
char cursor(int x, int y) {
	HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);
	char buf[2]; COORD c = { x,y }; DWORD num_read;
	if (!ReadConsoleOutputCharacter(hStd, (LPTSTR)buf, 1, c, (LPDWORD)&num_read))
		return '\0';
	else
		return buf[0];
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
		for (int x = 0; x < screen_x; ++x) {
			fill_data_to_buffer(x, y, ' ', 7);
		}
	}
}

void init_star() {
	for (int i = 0; i < scount; i++) {
		star[i].X = rand() % screen_x + 1;
		star[i].Y = rand() % screen_y + 1;
		fill_data_to_buffer(star[i].X , star[i].Y, '*', 6);
	}
	fill_buffer_to_console();
}
void fill_star_to_buffer() {
	for (int i = 0; i < scount; i++) {
		fill_data_to_buffer(star[i].X, star[i].Y, '*', 7);
	}
}
void star_fall() {
	int i;
	for (i = 0; i < scount; i++) {
		if (star[i].Y >= screen_y - 1) {
			star[i] = { (rand() % screen_x),1 };
		}
		else {
			star[i] = { star[i].X, star[i].Y + 1 };
		}
	}
}
void random_star(int star_add) {
	for (int c = 1; c <= star_add; c++) {
		for (int i = 0; i < scount; i++) {
			if (cursor(star[i].X, star[i].Y) != '*') {
				randomAgain:
				star[i].X = rand() % screen_x + 1;
				star[i].Y = rand() % screen_y + 1;
				if (cursor(star[i].X, star[i].Y) == '*') { goto randomAgain; }
				fill_data_to_buffer(star[i].X, star[i].Y, '*', 6);
				fill_buffer_to_console();
				break;
			}
		}
	}
}

void draw_ship(int ship_x, int ship_y, int type, int *color) {
	while (type == 1 && (*color > 15 || *color == 0)) { *color = rand() % 256; }
	for (int i = 0; i < strlen(myShip); i++) {
		if (type == 1)		{ 
			fill_data_to_buffer(ship_x + i, ship_y, myShip[i], *color); }
		//else if (type == 2)	{ fill_data_to_buffer(ship_x + i, ship_y, myShip[i], 5);}
		else if (type == 0) { fill_data_to_buffer(ship_x + i, ship_y, ' ', 0);}
	}
	fill_buffer_to_console();
}

int main() {
	int i;
	srand(time_t(NULL));
	setConsole(screen_x, screen_y);
/*----------------------- Assignment 2 ---------------------*/
	init_star();
	//random_star(20);
	//i = 0;
	//while (i < 1000) {
	//	star_fall();
	//	clear_buffer();
	//	fill_star_to_buffer();
	//	fill_buffer_to_console();
	//	Sleep(200);
	//	i++;
	//}

	bool play = true ;
	DWORD numEvents = 0;
	DWORD numEventsRead = 0;
	setConsole(screen_x, screen_y);
	setMode();
	while (play) {
		//star_fall();
		//clear_buffer();
		//fill_star_to_buffer();
		//fill_buffer_to_console();
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
						draw_ship(ship.X, ship.Y, 1, &shipColor);
					}
					//printf("press : %c\n", eventBuffer[i].Event.KeyEvent.uChar.AsciiChar);
				}
				else if (eventBuffer[i].EventType == MOUSE_EVENT) {
					int posx = eventBuffer[i].Event.MouseEvent.dwMousePosition.X;
					int posy = eventBuffer[i].Event.MouseEvent.dwMousePosition.Y;
					if (eventBuffer[i].Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED) {
						shipColor = rand() % 256;
						draw_ship(ship.X, ship.Y, 1, &shipColor);
					}
					else if (eventBuffer[i].Event.MouseEvent.dwButtonState & RIGHTMOST_BUTTON_PRESSED) {
						printf("right click\n");
					}
					else if (eventBuffer[i].Event.MouseEvent.dwEventFlags & MOUSE_MOVED) {
						draw_ship(ship.X, ship.Y, 0, &shipColor);
						ship.X = posx /*- (strlen(myShip)/2)*/;
						ship.Y = posy ;
					}
						int newStar = 0;
						for (int i = 0; i < strlen(myShip); i++) {
							if (cursor((ship.X + /*(strlen(myShip) / 2)*/ +i), ship.Y) == '*') {
								newStar++;
							}
						}
						draw_ship(ship.X, ship.Y, 1, &shipColor);
						random_star(newStar);
				}
			}
			delete[] eventBuffer;
		}
		Sleep(100);
	}
	return 0;
}