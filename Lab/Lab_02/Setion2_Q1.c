#include<stdio.h>
int main() {
    int n;
    printf("Enter number : ");
    scanf("%d", &n);
    printf("Factoring Result : ");

    // เลขที่ป้อนเป็นจำนวนเฉพาะไหม
    int c = 2;
    while (n%c > 0 || n == 2) {
       if (n/c == 1) { 
          printf("%d", n);
          break;
       }
       c = c+1;
    }

    // หาตัวประกอบ
    int a = 2;
    int b = 1;
    int m = n ;
    while (a <= n-1) {
        while(m%a == 0){
        // หาจำนวนเฉพาะ ที่เป็นตัวประกอบ
            int c = 2;
            while (n%c > 0) {
                if (n/c == 1) {break;}
                c = c+1;
            }   
        // พิมพ์ตัวประกอบ   
            m = m/a;   

            // พิมพ์เครื่องหมายคูณ
            b = b*a;
            if (b == n) {printf("%d", a); break;}
            printf("%d x ", a);
        }
        a = a+1;
    }
    return 0;
}
