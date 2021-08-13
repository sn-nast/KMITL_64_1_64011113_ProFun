// Level 1
#include<stdio.h>
#include<math.h>
int y = 0;
int check_L(double x) {
    if (x <= 0) {
        printf("%.4lf is not legth of side, Please enter positive number.\n", x);
        y = 1;
    }
    else { y = 0;}
    return y;
}

int main() {
    double a, b, c, x = 0, s, A;
    printf("Find area of Triangle\n");
    while (x != 2) {
        x = 0;
        printf("Enter the length of first side  : ");
        scanf("%lf", &a);    
        printf("Enter the length of second side : ");
        scanf("%lf", &b);
        printf("Enter the length of third side  : ");
        scanf("%lf", &c);

    // Heron's Formula
        s = (a+b+c)/2;
        A = sqrt(s*(s-a)*(s-b)*(s-c));

        if (check_L(a) == 1 || check_L(b) == 1 || check_L(c) == 1 ) {x = 1;}
        else if (A == 0 || (s-a)*(s-b)*(s-c) < 0) {
            printf("Please try again, because it not side of Triangle.\n\n");
            x = 1;
        }    
        else {x = 2;}
    }
    printf("Area = %.4lf", A);
    return 0;
}
