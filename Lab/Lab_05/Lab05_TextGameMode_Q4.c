#include<stdio.h>
#include<Windows.h>
#include<conio.h>
#include<string.h>

char Ship[20] = " <-0-> ";
int maxWidth = 80;      // กำหนดความกว้างสูงสุดที่เคลื่อนที่ได้
int maxHeight = 30;     // กำหนดความสูงสูงสุดที่เคลื่อนที่ได้

void draw_ship() {
    printf("%s", Ship);    
}

void gotoxy(int x, int y) {
    COORD c = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void erase_ship(int x, int y) {
    gotoxy(1, y);
    for(int c = 1; c <= maxWidth; c++ ) {printf(" ");}
    gotoxy(x, y);
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
                if (x <= 0) { x = 0; }             
                else {
                    gotoxy(--x,y);
                    draw_ship();
                }
            }
            if(ch == 'd') {
                if (x >= maxWidth-lenShip) { x = maxWidth-lenShip; } 
                else {
                    gotoxy(++x,y);
                    draw_ship();
                }
            }
            if(ch == 'w') {
                if (y <= 0) { y = 0;} 
                else {
                    erase_ship(x, y);
                    gotoxy(x,--y);
                    draw_ship();
                }
            }
            if(ch == 's') {
                if (y >= maxHeight) { y = maxHeight;} 
                else {
                    erase_ship(x, y);
                    gotoxy(x,++y);
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
