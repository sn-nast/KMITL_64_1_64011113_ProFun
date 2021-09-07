#include<stdio.h>
#include<windows.h>
#include<conio.h>

void draw_MeMan(int);
void gotoxy(int, int);
void control(char, int, int);

int main() {
	int x = 5, y = 10;
	gotoxy(x, y);
	for (int x1 = x; x1 < 20; x1++) {
		gotoxy(x1, y);
		draw_MeMan(10);
	}
	char ps = ' ';
	do {
		if (_kbhit()) {
			ps = _getch();
			control(ps, x, y);
		}
	} while (ps != 'x');
	return 0;
}

void draw_MeMan(int time) {
	char Me[20] = "<-_->";
	printf(" %s ", Me);
	Sleep(time);
}

void gotoxy(int x, int y) {
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void control(char press, int x, int y) {
	int time = 100;
	if (press == 'a') {
		gotoxy(--x, y);
		draw_MeMan(time);
	}
	if (press == 'd') { 
		gotoxy(--x, y);
		draw_MeMan(time); 
	}
	fflush(stdin);
}