// 64011113
// ProFun Activity 06 : Pass by Reference
#include<stdio.h>

void swap(int *x, int* y){
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;

}
int main(){
    int a, b;
    scanf_s("%d %d", &a, &b);
    swap(&a, &b);
    printf("%d %d", a, b);
    return 0;
}   