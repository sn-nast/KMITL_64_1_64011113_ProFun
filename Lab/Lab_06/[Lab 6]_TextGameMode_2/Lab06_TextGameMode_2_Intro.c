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
	gotoxy(x, y); printf(" <-0-> ");
}

int main()
{
	setcolor(6, 8);
	setcursor(0);
	char ch = '.';
	int x = 38, y = 20;
	draw_ship(x, y);
	do {
		if (_kbhit()) {
			ch = _getch();
			if (ch == 'a') { draw_ship(--x, y); }
			if (ch == 'd') { draw_ship(++x, y); }
			fflush(stdin);
		}
		Sleep(100);
	} while (ch != 'x');
	return 0;
}	
