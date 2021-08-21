#include<stdio.h>

int main()
{
    double num = .3;
    num*=2;
    printf("= %f\n", num);
    for(; num > 0 ; ){
        if(num >= 1) {num-=1; printf("1");}
        else {printf("0");}
        num*=2;
    
    }

    return 0;
}