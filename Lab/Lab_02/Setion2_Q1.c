#include<stdio.h>
int main() {
    int n;
    printf("Enter number : ");
    scanf("%d", &n);
    printf("Factoring Result : ");

    // หาตัวประกอบ
    int a = 2;
    int b = 1;
    int m = n ;
    while (a <= n) {
        while(m%a == 0){
            m/=a;  
            b*=a;
            if (b == n) {printf("%d", a); break;}
            printf("%d x ", a);
        }
        a = a+1;
    }
    return 0;
}