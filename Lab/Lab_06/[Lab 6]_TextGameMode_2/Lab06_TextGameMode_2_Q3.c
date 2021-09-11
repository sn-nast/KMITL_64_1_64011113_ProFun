#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<stdbool.h>

void setcolor(int fg, int bg) // Set color
// fg = foreground , bg = background
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, bg * 16 + fg);
}

void setcursor(bool visible) // Set cursor
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console, &lpCursor);
}

void gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void draw_ship(int x, int y)
{
	gotoxy(x, y); 
	setcolor(7, 0);
	printf(" ");		
	setcolor(2, 4);
	printf("<-0->");		// shipLen = 1+5+1 = 7
	setcolor(7, 0);
	printf(" ");
}

void bulletMove(int x, int y) {
	x = x + 2;
	y = y - 2;
	int bulletLen = 3;	
	gotoxy(x, y);
	printf("!!!");		// bulletLen = 3

	for (int i = y; i > 0; i--) {
		gotoxy(x, i);
		setcolor(6, 0);
		printf("!!!");		// bulletLen = 3
		Sleep(100);
		if(i != y){
			Sleep(1000);
			for (int i = y; i >= 0; i--) {
				gotoxy(x, i + 1);
				setcolor(7, 0);
				for (int c = 0; c < bulletLen; c++) {printf(" ");}
			}
		}
	}
}

int main() {
	setcursor(0);
	char ch = '.';
	int x = 38, y = 20, shipLen = 7;
	int maxWidth = 80;
	char direction = ' ';
	char bullet = 'F';
	draw_ship(x, y);
	do {

		if (_kbhit()) {
			ch = _getch();
			if (ch == 'a') {
				if (x <= 0) { x = 0; }
				else {direction = 'L';}
			}
			if (ch == 'd') {
				if (x >= maxWidth - shipLen) { x = maxWidth - shipLen; }
				else {direction = 'R';}
			}
			if (ch == 's') {direction = ' ';}
			if (ch == ' ') { bullet = 'N'; }
			fflush(stdin);
		}

		if (direction != ' ') {
			if (direction == 'L') {
				if (x <= 0) { x = 0; }
				else draw_ship(--x, y);
			}
			if (direction == 'R') {
				if (x >= maxWidth - shipLen) { x = maxWidth - shipLen; }
				else draw_ship(++x, y);
			}
		}

		while (bullet == 'N') {
			//bulletMove(x, y);
			int xB = x + 2;
			int yB = y - 2;
			int bulletLen = 3;
			for (int i = yB; i > 0; i--) {
				gotoxy(xB, i);
				setcolor(6, 0);
				printf("!!!");		// bulletLen = 3
				Sleep(10);
				if (i != y) {
					Sleep(10);
					for (int i = yB; i >= 0; i--) {
						gotoxy(xB, i + 1);
						setcolor(7, 0);
						for (int c = 0; c < bulletLen; c++) { printf(" "); }
					}
				}
			}
		bullet = 'F';	
		}
		Sleep(100);
		} while (ch != 'x');
}
