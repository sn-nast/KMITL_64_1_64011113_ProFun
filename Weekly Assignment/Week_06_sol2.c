// Level 3
// 64011113
/* 94.	เกมการแข่งขันนับเลข เป็นเกมการแข่งขันที่มีผู้เล่น 2 คน ผลัดกันนับเลขโดยนับเลขได้น้อยที่สุด 1 เลขสูงสุดทีละ m เลข 
จากเลข 1 ไปจนถึงเลข n ใครเป็นผู้นับเลข n จะเป็นฝ่ายแพ้ ถ้าเราเป็นฝ่ายนับเลขคนแรกเสมอ 
จงเขียนโปรแกรมแสดงชุดตัวเลขที่ถ้านับให้ถึงเลขนั้นทุกรอบจะไม่มีวันแพ้ ถ้าไม่สามารถทำได้ แสดงผล Error (Level 3) */
// Sol 2

/* ------------------------------------------------------------------------------------------
    - ผมจำตัวแปรผิดครับ เลยทำให้ผมสลับตัวแปรกัน ระหว่าง m กับ n 
    - ผมขอพัฒนาเป็นเกมที่สามารถให้เลือกได้ว่า จะให้ใครเป็นผู้เริ่มเกมก่อน 
      (ถ้าคอมเริ่มก่อนจะชนะเสมอ แต่กรณีที่ m/(n+1) ได้เศษเป็น 1 จะมีโอกาสชนะทั้งสองฝ่าย เว้นแต่ผู้เล่นจะพลาดเอง)
    - เนื่องจากผมทราบวิธีการหาค่าที่ชนะ หรือ แพ้ อยู่แล้ว (ตามวิธีในวิธีทำที่ 1) ผมพยายามหาวิธีอื่นๆแล้ว 
      แต่ผมไม่สามารถอธิบายได้ ผ่านการเขียนโปรแกรมได้ เลยใช้การทำเกมแทนนะครับ
    - ผมสามารถแสดงผลลัพธ์ออกมาตามโจทย์ได้ แต่คำตอบจะไม่สอดคล้องกับการเล่นแต่ละรอบ ผมจึงละไว้นะครับ
 --------------------------------------------------------------------------------------------- */
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
    if ((c_now > n + 1)){ 
        badNumNow = badNumNext;
        badNumNext += (n + 1); 
        if(badNumNext <= c_now){
            badNumNext += (n+1);
            badNumNow = badNumNext;
        }
    }

    if(c_now >= badNumNow){
        badNumNow = badNumNext;
        badNumNext = badNumNext + (n+1);
    }
    

    if(c_now + n < badNumNow || c_now + n == badNumNow || c_now + 1 < badNumNow ){
        for (int c = c_now + 1; c < badNumNow && c_now <= myLast +(n + 1); c++){
            if (badNumNow - c <= n) {
                printf("%d ", c);
                c_now += 1;
            }
        }
    }
    else if (c_now + n > badNumNow || c_now == badNumNow) {
        int randCount = rand()%(n) + 1 ;
        for(int c = c_now + 1 ; c - yourLast <= n && c_now - c <= randCount; c++){
            c_now += 1;
            if((c_now == m  && c != c_now )|| (c_now == badNumNow && c_now != 1 && c != c_now)) {
                c_now -= 1;
                break;
            }
            else if(c_now == m && c == c_now) {
                printf("%d", c);
                break ;
            }
            printf("%d ", c);
        }
    }
    myLast = c_now;
    printf("\n");
}

int main(){
    int n = 0, m = 0 ;
    char choose;
    printf("Count game\n");
    printf("You VS Computer\n\n");
    while (m <= n){
        printf("enter Max step (n)    : ");
        scanf("%d", &n);
        printf("enter Max count (m)   : ");
        scanf("%d", &m);
        if(m <= n) {printf("Please enter again, Max count (m) > Max step (n)\n");}
    }
    
   
    fflush(stdin);
    c_now = 0;
    printf("First turn, YOU or COMPUTER? (enter Y or C) : ");
    scanf(" %c", &choose);
    printf("\n");

    for (int c = 0; c <= n + 1; c++)  {
        if(c % (n + 1) == m % (n + 1)){
            badNumNow = c;
            badNumNext = c + (n + 1);
            continue;
        }
    }
    if(choose == 'c'|| choose == 'C'){
        while (c_now < m){
            myTurn(n, m);
            if(myLast != m) {yourTurn(n, m);}
        }
    }
    else if (choose == 'y' || choose == 'Y'){      
        while (c_now < m){
            yourTurn(n, m);
            if(yourLast != m) {myTurn(n, m);}
        }
    }
    if(myLast >= m){
        printf("\nYOU WIN!!!");
    }
    else if(yourLast >= m){
        printf("\nYOU LOSE!!!");
    }
    return 0;
}
