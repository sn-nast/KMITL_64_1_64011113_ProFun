// Level 1
#include<stdio.h>
#include<math.h>
int main() {
    double a, b, c, s, A = 0;
    printf("Find area of Triangle\n");
    while (A == 0 || (s-a)*(s-b)*(s-c) < 0){
        a = 0; 
        b = 0; 
        c = 0;

        while (a <= 0) {
            printf("Enter the length of first side  : ");
            scanf("%lf", &a);    
            if (a <= 0) { printf("%.4lf is not legth of side, Please enter positive number.\n\n", a); }
        }
        while (b <= 0) {
            printf("Enter the length of second side : ");
            scanf("%lf", &b);    
            if (b <= 0) { printf("%.4lf is not legth of side, Please enter positive number.\n\n", b); }
        }
        while (c <= 0) {
            printf("Enter the length of third side  : ");
            scanf("%lf", &c);    
            if (c <= 0) { printf("%.4lf is not legth of side, Please enter positive number.\n\n", c); }
        }

    // Heron's Formula
        s = (a+b+c)/2;
        A = sqrt(s*(s-a)*(s-b)*(s-c));

        if (A == 0 || (s-a)*(s-b)*(s-c) < 0) { printf("Please try again, because it not side of Triangle.\n\n");}    
    } 
    printf("Area = %.4lf", A);
    return 0;
}
 