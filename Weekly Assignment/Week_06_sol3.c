// Level 3
// 64011113
/* 94.	เกมการแข่งขันนับเลข เป็นเกมการแข่งขันที่มีผู้เล่น 2 คน ผลัดกันนับเลขโดยนับเลขได้น้อยที่สุด 1 เลขสูงสุดทีละ m เลข 
จากเลข 1 ไปจนถึงเลข n ใครเป็นผู้นับเลข n จะเป็นฝ่ายแพ้ ถ้าเราเป็นฝ่ายนับเลขคนแรกเสมอ 
จงเขียนโปรแกรมแสดงชุดตัวเลขที่ถ้านับให้ถึงเลขนั้นทุกรอบจะไม่มีวันแพ้ ถ้าไม่สามารถทำได้ แสดงผล Error (Level 3) */
// Sol 2

// ? A B นับกันได้ระหว่าง 1 - m
int way_n(){

} 
int main2(){
}

#include<stdio.h> 
#include<stdlib.h>
int c_now;
int myLast, yourLast;
void yourTurn(int n, int m){
    printf("Your turn   : ");
    char enter = 0;
    while(enter != '\r' && enter != '\n'){
        scanf("%d", &yourLast);
        enter = getchar();
        if(enter == '\n') {continue;} 
    }
    if(yourLast - c_now > n || yourLast <= myLast || yourLast > m){
        printf("Wrong enter, please try again\n");
        if(c_now == 1) {yourLast = c_now ;}
        else {yourLast = 0;}
        yourTurn(n, m);
    }
    c_now = yourLast;
}

int badNumNext, badNumNow ;
void myTurn(int n, int m){
    printf("COM turn    : ");
    int Re = m % (n+1);
    int worstNum = m - (n + 1);
    if ((badNumNext + (n + 1)) % (n + 1) == Re && (c_now > n + 1)){ 
        badNumNow = badNumNext;
        badNumNext += (n + 1); 
    }
    if(c_now >= badNumNow){
        badNumNow = badNumNext;
    }

    if(c_now + n < badNumNow || c_now + 2 == badNumNow){
        for (int c = c_now + 1; c < badNumNow && c_now <= myLast +(n + 1); c++){
            if (badNumNow - c <= n) {
                printf("%d ", c);
                c_now += 1;
            }
        }
    }
    else if (c_now + 1 == badNumNow || c_now == badNumNow) {
        int randCount = rand()%(n) + 1 ;
        for(int c = c_now + 1 ; c - yourLast <= n && c_now - c <= randCount; c++){
            if(c_now == m) {break;}
                printf("%d ", c);
                c_now += 1;
        }
    }
    myLast = c_now;
    printf("\n");
}


int modFun(int x, int y){
    // x % y
    int k, answer;
    int n = x/y;
    answer = x - (n*y);
    return answer;
}
int main(){
    int n, m;
    int x, y;
    printf("Count game\n");
    printf("enter Max step (m)    : ");
    scanf("%d", &m);
    printf("enter Max count (n)   : ");
    scanf("%d", &n);

    for(int c = 1 ; c <= n; c++){
        if( modFun(c, m + 1 ) == modFun(n, m + 1) ) {
            if (c-1 == 0) {
                printf("ERROR");
                break;
            }
            printf("%d ", c-1);
        }
        if(c == 1) {printf("way to win : ");}
    }
}