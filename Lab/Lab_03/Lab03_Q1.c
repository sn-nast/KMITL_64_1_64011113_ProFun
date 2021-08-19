#include<stdio.h>
int lastSum;

int digitSum(int num){
    int sum = 0;
    while(num > 0) {                 
        int digit = num % 10;   // แยกตัวเลขตัวสุดท้าออกก        
        sum += digit;           // รวมตัวเลขนั้น 
        num /= 10;              // เก็บตัวเลขที่เหลือ 
        printf("%d", digit);
        // แสดงในรูปการบวก   
        if (num == 0)   {printf (" = %d \n", sum);}
        else            {printf (" + ");}
    }
    lastSum = sum;
    return lastSum;
}

int main() {
    int num;
    printf("input number : ");
    scanf("%d", &num);
    if (num > 0) {
        int c = 1 ;
        printf("\nDigit sum (round %d) : ", c);
        // แยกตัวเลขออกแต่ละตัว แล้วบวกรวมกัน
        digitSum (num);
        // ถ้าสามารถแยกตัวเลขออกได้อีก ให้แยกแต่ละตัว แล้วบวกรวมกัน
        while(lastSum >= 10) {
            c++;
            printf("Digit sum (round %d) : ", c);
            digitSum (lastSum);
        }
    }
    printf("Final digit sum : %d\n", lastSum);
    return 0;
}

