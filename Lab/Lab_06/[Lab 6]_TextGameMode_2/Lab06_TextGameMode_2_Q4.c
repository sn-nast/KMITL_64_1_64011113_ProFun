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

void draw_bullet(int x, int y) {
	//x = x + 2;
	//y = y - 1;
	gotoxy(x, y);
	setcolor(6, 0);
	printf("!!!");		// bulletLen = 3
	setcolor(7, 0);
}

void erase_bullet(int x, int y) {
	//x = x + 2;
	//y = y - 1;
	gotoxy(x, y);
	printf("   ");		// bulletLen = 3
}

int main() {
	setcursor(0);
	char ch = '.';
	int x = 38, y = 20, shipLen = 7;
	int maxWidth = 80;
	char direction = ' ';
	int bullet  = 0;		// no bullet = 0
	//int bullet_remain = 5;
	int xb[5], yb[5];
	//int* ptr_bullet;
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
			if (bullet < 5 && ch == ' ') {
				bullet++;
				xb[bullet - 1] = x + 2;		// 1/3 of ship = 2 
				yb[bullet - 1] = y - 1;
			}
			fflush(stdin);

		}
		if (x <= 0) { direction = 'R'; }
		if (x >= maxWidth - shipLen) { direction = 'L'; }
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

		if (bullet != 0) {
			int bullet2 = bullet;
			//for (int c = 1; c-1 < bullet; c++) {
			//	erase_bullet(xb[c-1], yb[c-1]);
			//	if (yb[c-1] == 1) { bullet--; }
			//	else draw_bullet(xb[c-1], --yb[c -1]);
			//}
			erase_bullet(xb[bullet-1], yb[bullet-1]);
			if (yb[bullet-1] == 1) { bullet--; }
			else draw_bullet(xb[bullet-1], --yb[bullet -1]);

		}
		Sleep(10);
		} while (ch != 'x');
}
