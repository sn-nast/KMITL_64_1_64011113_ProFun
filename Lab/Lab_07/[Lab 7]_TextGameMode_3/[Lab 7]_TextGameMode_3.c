#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<time.h>
#include<stdbool.h>			// in C programming


void gotoxy(int x, int y){
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void draw_ship(int x, int y){
	gotoxy(x, y); printf(" <-0-> ");
}

void draw_bullet(int x, int y){
	gotoxy(x, y); printf("^");
}

void clear_bullet(int x, int y){
	gotoxy(x, y); printf(" ");
}

//[ADD] invisible cursor
void setcursor(bool visible){
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console, &lpCursor);
}

char cursor(int x, int y) {
	HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);
	char buf[2]; COORD c = { x,y }; DWORD num_read;
	if (!ReadConsoleOutputCharacter(hStd, (LPTSTR)buf, 1, c, (LPDWORD)&num_read))
		return '\0';
	else
		return buf[0];
}

void randomStar(int n) {
	for (int si = 1; si <= n; si++) {
		int xi, yi, xiMin = 10, xiMax = 70, yiMin = 2, yiMax = 5;
		check :
			xi = rand() % (xiMax + 1);
			yi = rand() % (yiMax + 1);
			if (xi < xiMin) { xi += xiMin; }
			if (yi < yiMin) { yi += yiMin; }
		if (cursor(xi, yi) == '*'	  || 
			cursor(xi + 1, yi) == '*' || 
			cursor(xi - 1, yi) == '*' ||
			cursor(xi, yi + 1) == '*' ||
			cursor(xi, yi - 1) == '*'	) { 
			goto check;
		}
		gotoxy(xi, yi);
		printf("*");
	}
}

int main() {
	srand(time(NULL));
	setcursor(0);
	char ch = '.';
	int x = 38, y = 20;
	int bx, by;
	int bullet = 0;
	int score = 0;

	// SETUP
	/* ------------------- Assignment 1 ------------------- */
	// Random star
	randomStar(20);
	draw_ship(x, y);

	// IN GAME
	do {
		// Move
		if (_kbhit()) {
			ch = _getch();
			if (ch == 'a') { draw_ship(--x, y); }
			if (ch == 's') { draw_ship(++x, y); }
			if (bullet != 1 && ch == ' ') { 
				bullet = 1; 
				bx = x + 3; 
				by = y - 1; }
			fflush(stdin);
		}
		// Bullet
		if (bullet == 1) {
			clear_bullet(bx, by);
	/* ------------------- Assignment 2 ------------------- */
	// Beep			
			Beep(700, 20);
			if (by == 2) { bullet = 0; }
			else { 
	/* --------------- Assignment 3 Part 1 ---------------- */
	// Clear star and New random star
				if(cursor(bx, by - 1) == '*') {
					gotoxy(bx, by - 1);
					printf(" ");
					Beep(1000, 50);
					bullet = 0;
					score++;
					randomStar(1);
				}
				else draw_bullet(bx, --by); 
			}
		}
	/* --------------- Assignment 3 Part 2 ---------------- */
	// Score
		gotoxy(80, 2);
		printf("Score : %d", score);
		Sleep(100);
	} while (ch != 'x');
	return 0;
}