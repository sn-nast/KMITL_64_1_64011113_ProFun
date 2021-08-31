#include<stdio.h>
#include<Windows.h>

void draw_ship() {
    printf(" <-0-> ");      //เว้นวรรคหน้า ยาน
}

void gotoxy(int x, int y) {
    COORD c = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}


int main() {
    int maxWidth = 80;
    for (int i = 1; i <= maxWidth; i++) {
        gotoxy(i, 20);
        draw_ship();
        Sleep(500);
    }
    return 0;
}