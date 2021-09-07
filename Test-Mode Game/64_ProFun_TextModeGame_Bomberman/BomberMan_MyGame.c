#include<stdio.h>
#include<windows.h>
#include<conio.h>

int draw_MeMan(int, int);
void gotoxy(int, int);
void control(char, int, int, int*, int*);
void arrowNow2(char, int, int);
void bomb();
int xMax = 80, yMax = 30, MeLen;

int main() {
	int x = 0, y = 10;
	int timeDelay = 10;
	gotoxy(x, y);
	draw_MeMan(x, y);
	char ps = ' ';
	do {
		if (_kbhit()) {

			ps = _getch();
			int xNew, yNew;
			control(ps, x, y, &xNew, &yNew);
			x = xNew;
			y = yNew;
			//Sleep(timeDelay);
		}
	} while (TRUE);
	return 0;
}

int draw_MeMan(int x, int y) {
	gotoxy(x, y);
	//printf("/\\__/\\ \n");
	//printf("|^  ^|\n");
	//printf("| -- |\n");
	//printf("|____|\n");

	char Me[20] = " M ";
	MeLen = strlen(Me);
	printf("%s", Me );
	return MeLen;
}

void gotoxy(int x, int y) {
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void arrowNow2(char press, int x, int y) {
	Sleep(100);
	gotoxy(x - 1, y);
	printf(" ");
	gotoxy((x + MeLen) - 1, y);
	printf(" ");
}


void bomb(){
	printf("bomb");
}
void control(char press, int x, int y, int* xNew, int* yNew) {
	int arrowNow;
	if (press == 'a') {
		if (x <= 0) { x = 0; }
		else {
			gotoxy(x - 2, y);
			printf("<");
			draw_MeMan(--x, y);
		}
	}
	if (press == 'd') {
		if (x >= xMax - MeLen) { x = xMax - MeLen; }
		else {
			gotoxy(x + 1 + MeLen, y);
			printf(">");
			draw_MeMan(++x, y);
		}
	}
	if (press == 'w') {
		if (y <= 0) { y = 0; }
		else {
			gotoxy(x, y);
			for (int i = 0; i < MeLen; i++) printf(" ");
			draw_MeMan(x, --y);
		}
	}
	if (press == 's') {
		if (y >= yMax) { y = yMax; }
		else {
			gotoxy(x, y);
			for (int i = 0; i < MeLen; i++) printf(" ");
			draw_MeMan(x, ++y);
		}
	}
	if (press == ' ') {
		gotoxy(x, y);
		for (int i = 0; i < MeLen; i++) printf(" ");
		gotoxy(x + (MeLen / 3), y);
		printf("B");
	}
	*xNew = x;
	*yNew = y;
	fflush(stdin);
}