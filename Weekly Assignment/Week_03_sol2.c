// Level 2
#include<stdio.h> 

int main(){
    int n ;
    scanf("%d", &n);
    for (int cL = 1; cL<= n; cL++) {
        int cP = 1;
        if (cL%2 > 0) 
            for (cP; cP <= (n+1)/2; cP++) {printf("* ");}
        else  
            for (cP; cP <= n/2; cP++) {printf(" *");}
        printf("\n");
    }
    return 0;
}
