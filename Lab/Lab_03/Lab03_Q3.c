#include<stdio.h>
int main () {
    int n, i, j,c;
    printf("input : ");
    scanf("%d", &n);
    printf("\n");
    // พิมพ์ส่วนบน บรรทัดที่ 1 ถึง n
    // แถว i / คอลัมน์ j
    for(i = 1; i <= n; i++) {
        // พิมพ์ปีกซ้ายบน
        for(j = 1; j <= i; j++)             {printf("* ");}
        // พิมพ์ช่องว่างบน
        for(c = 1; c <= (2*n-1)-(2*i); c++) {printf("  ");}
        // พิมพ์ปีกขวาบน
        for(j = 1; j<=i; j++) {
            if (j == n && i == n)   {break;}
            else                    {printf("* ");}
        }
        printf("\n");
    }
    // พิมพ์ส่วนล่าง บรรทัดที่ n ถึง 2n-1 (เริ่มนับที่ 1 ถึง n-1)
    for(i = 1; i <= n-1; i++) {
        // พิมพ์ปีกซ้ายล่าง
        for(j = 1; j <= n-i; j++)       {printf("* ");}
        // พิมพ์ช่องว่างล่าง (ช่องว่างที่ต้องมี 2i-1)
        for(c = 1; c <= (2*i)-1; c++)   {printf("  ");}
        // พิมพ์ปีกขวาล่าง
        for(j = 1; j <= n-i; j++)       {printf("* ");}
        printf("\n");
    }  
    return 0;
}

