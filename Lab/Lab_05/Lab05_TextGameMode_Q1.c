#include<stdio.h>
#include<Windows.h>

void draw_ship() {
    printf(" <-0-> ");       //เว้นวรรคหน้า ยาน
}

void gotoxy(int x, int y){
    COORD c = {x, y};
    SetConsoleCursorPosition (GetStdHandle(STD_OUTPUT_HANDLE), c);
}


int main() {
    int position[2] ;
    printf("Enter X position : ");
    scanf("%d", &position[0]);
    printf("Enter Y position : ");
    scanf("%d", &position[1]);

    gotoxy(position[0], position[1]);
    draw_ship();
 
    return 0;
}