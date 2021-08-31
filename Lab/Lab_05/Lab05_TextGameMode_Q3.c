#include<stdio.h>
#include<Windows.h>
#include<conio.h>
#include<string.h>

char Ship[20] = "<-0->";

void draw_ship() {
    printf(" %s ", Ship);    
}

void gotoxy(int x, int y) {
    COORD c = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

int main() {
    char ch = ' ';
    int x = 38 , y = 20 ;
    int lenShip = strlen(Ship);
    gotoxy(x, y);
    draw_ship();
    do { 
        if (_kbhit()) {
            ch = _getch();
            if(ch == 'a') {
                if (x <= 0) { x = 0; }             // เมื่อกำหนดให้ความกว้างที่เคลื่อนที่ได้ รวมระยะตัวยานด้วย
                else {
                    gotoxy(--x,y);
                    draw_ship();
                }
            }
            if(ch == 'd') {
                if (x >= 80-lenShip) { x = 80-lenShip; }     // เมื่อกำหนดให้ความกว้างที่เคลื่อนที่ได้ รวมระยะตัวยานด้วย
                else {
                    gotoxy(++x,y);
                    draw_ship();
                }
            }
            fflush(stdin);
        }
        Sleep(100);
    } 
     while (ch != 'x');
return 0;
}
