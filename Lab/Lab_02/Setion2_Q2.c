#include<stdio.h>
int main() {
    int n, m;
    printf("Enter first number : ");
    scanf("%d", &n);
    printf("Enter second number : ");
    scanf("%d", &m);

    // หา หรม.
    int c = 2, x = 1, Rn = n, Rm = m;
    while (c <= Rn && c <= Rm) {
        while (Rn%c == 0 && Rm%c == 0) { 
          Rn/=c;
          Rm/=c;
          x*=c;
       }
       c+=1;
    }
    printf("Greatest common divisor = %d", x);
    return 0;
}
