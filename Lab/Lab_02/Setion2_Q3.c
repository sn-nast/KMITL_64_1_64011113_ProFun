#include<stdio.h>
int main() {
    int x, y, n;
    printf("Enter number : ");
    scanf("%d", &n);
    // row check
    for (x = 1; x <= n; x++){
    // column check
        for(y = 1; y <= n; y++){
            // output
            if (x==n || x==1 || y==n || y==1){
                printf("*");
            }
            else printf(" ");
        }
        printf("\n");
    }
    return 0;
}
