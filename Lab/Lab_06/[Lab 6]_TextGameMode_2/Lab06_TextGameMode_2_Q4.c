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
	gotoxy(x, y);
	setcolor(6, 0);
	printf("!!!");		// bulletLen = 3
	setcolor(7, 0);
}

void erase_bullet(int x, int y) {
	gotoxy(x, y);
	printf("   ");		// bulletLen = 3
}


int main() {
	/*  ------------------- Assignment 1 ---------------------- */
	/* NO Cursor */
	setcursor(0);
	char ch = '.';

	int x = 38, y = 30, shipLen = 7;
	int maxWidth = 80;
	char direction = ' ';

	int xbl[6], ybl[6];
	int bullet = 0;		// no bullet = 0
	int bulletRe = 5, bulletAdd = 0, bulletRun = 0;
	int bulletNo[5] = { 0, 0, 0, 0, 0 };
	int* pt_bulletNo = bulletNo;

	draw_ship(x, y);
	do {
		if (_kbhit()) {
			ch = _getch();
			if (ch == 'a' || ch == 'A') {
				if (x <= 0) { x = 0; }
				else {direction = 'L';}
			}
			if (ch == 'd' || ch == 'D') {
				if (x >= maxWidth - shipLen) { x = maxWidth - shipLen; }
				else {direction = 'R';}
			}
			if (ch == 's' || ch == 'S') {direction = ' ';}
 			if (bullet < 5 && ch == ' ') {
				bullet++;
				for (int i = 1; i <= 5; i++) {
					if (bulletNo[i - 1] != 1 ) {
						xbl[i - 1] = x + 2; // 1/3 of ship = 2 
						ybl[i - 1] = y - 1;
						break;
					}
				}
			}
			fflush(stdin);
		}
		/*  ------------------- Assignment 2 ---------------------- */
		/* Auto move */
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
		/*  ------------------- Assignment 3 - 4 ---------------------- */
		/* Bullet */
		if (bulletRun < bullet) { bulletAdd = bullet - bulletRun ; }
		if (bullet != 0 || bulletRun != 0) {
			// have bullet add
       		bulletRun += bulletAdd;
			if (bulletAdd != 0) {
				int c_bulletAdd;
				if (bulletRun == bulletAdd) { c_bulletAdd = bulletAdd; }
				else if (bulletRun > bulletAdd) { c_bulletAdd = bulletAdd + 1; }
				for (int c = 1; c <= bulletAdd ; c++) {
					for (int i = 1; i <= 5; i++) {
						if (bulletNo[i - 1] != 1) {
							bulletNo[i - 1] = 1;
							bulletAdd--;
							if (bulletAdd == 0) { break; }
						}
					}
				}
			}
			// Bullet move (check bullet must run)
			for (int i = 1; i <= 5; i++) {
				// Have remain in bulletNo[1 - 5]?
    			if (bulletNo[i - 1] == 1) {
					erase_bullet(xbl[i - 1], ybl[i - 1]);
					if (ybl[i - 1] == 0) { 
						if(bullet > 0){
							bullet--;
							bulletRun--;
						}
						bulletNo[i - 1] = 0;
					}
					else draw_bullet(xbl[i- 1], --ybl[i - 1]);
				}
			}
		}
		Sleep(10);
	} while (ch != 'x'); 
}  
