#include<stdio.h>
int num_i = 1;
int num_f = 10000;
int sum_P;

void fun_P(int c1){
    // แสดงผล x ที่สามารถแทนค่าได้ตรงกับเงื่อนไขที่กำหนด (P(x) = x)
    printf("P(%d) = ", c1);
    sum_P = 0;
        for (int c2 = 1; c2 < c1; c2++){
            if (c1 % c2 == 0){
                sum_P+=c2;
                if(sum_P == c1) {printf("%d = %d", c2, sum_P);}
                else printf("%d + ", c2);
            }
        }
    printf("\n");
}

int main() {
    printf ("Check P(x) = x while x is %d to %d.\n\n", num_i, num_f);
    for(int c1 = num_i; c1 <= num_f; c1++){        
        sum_P = 0;
        for (int c2 = 1; c2 < c1; c2++){
            // c2 คือ ตัวที่สามารถหาร ตัวที่กำลังเช็คอยู่(c1) ว่าหารลงตัว
            if(c1%c2 == 0) {sum_P+=c2;}  
        }
        if(sum_P == c1) {fun_P(c1);}
    }
    return 0;
}