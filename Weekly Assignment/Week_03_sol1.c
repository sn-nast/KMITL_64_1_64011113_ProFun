// Level 2
#include<stdio.h> 

int main() {
    int n ;
    scanf("%d", &n);
    for(int cL = 1; cL <= n; cL++ ){
        for(int cP = 1; cP <= n ; cP++) {
            if(cL%2 > 0){
                if (cP%2 > 0)  {printf("*");}
                else           {printf(" ");}
            }
            else {
                if (cP%2 > 0)  {printf(" ");}
                else           {printf("*");}
            }
        }
        printf("\n");
    }
    return 0;
}
 