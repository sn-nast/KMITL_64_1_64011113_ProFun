// Level 3
// 64011113
/* 94.	เกมการแข่งขันนับเลข เป็นเกมการแข่งขันที่มีผู้เล่น 2 คน ผลัดกันนับเลขโดยนับเลขได้น้อยที่สุด 1 เลขสูงสุดทีละ m เลข 
จากเลข 1 ไปจนถึงเลข n ใครเป็นผู้นับเลข n จะเป็นฝ่ายแพ้ ถ้าเราเป็นฝ่ายนับเลขคนแรกเสมอ 
จงเขียนโปรแกรมแสดงชุดตัวเลขที่ถ้านับให้ถึงเลขนั้นทุกรอบจะไม่มีวันแพ้ ถ้าไม่สามารถทำได้ แสดงผล Error (Level 3) */
// Sol 1

#include<stdio.h> 

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