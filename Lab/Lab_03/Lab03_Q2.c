#include<stdio.h>
int num_i = 1;
int num_f = 10000;
int sum_P;

void fun_P(int x){
    // แสดงผล x ที่สามารถแทนค่าได้ตรงกับเงื่อนไขที่กำหนด (P(x) = x)
    printf("P(%d) = ", x);
    sum_P = 0;
    for (int c1 = 1; c1 < x; c1++){
        if (x % c1 == 0){
            sum_P+=c1;
            if(sum_P == x) {printf("%d = %d", c1, sum_P);}
            else printf("%d + ", c1);
        }
    }
    printf("\n");
}

int main() {
    printf ("Check P(x) = x while x is %d to %d.\n\n", num_i, num_f);
    for(int x = num_i; x <= num_f; x++){        
        sum_P = 0;
        for (int c1 = 1; c1 < x; c1++){
            // c1 คือ ตัวที่สามารถหาร ตัวที่กำลังเช็คอยู่(x) ว่าหารลงตัว
            if(x%c1 == 0) {sum_P+=c1;}  
        }
        if(sum_P == x) {fun_P(x);}
    }
    return 0;
}