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

int main() {
	setcolor(2, 4);
	setcursor(0);
	char ch = '.';
	int x = 38, y = 20, shipLen = 7;
	int maxWidth = 80;
	char direction = ' ';
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
		Sleep(100);
		} while (ch != 'x');
}