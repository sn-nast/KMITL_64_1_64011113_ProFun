// Level 4
// 64011113
/* 75. จงเขียนโปรแกรมหาค่า x + y โดยรับมาจาก “a.txt” และแสดงใน “b.txt” */
// Sol 1

#include<stdio.h> 

int main(){
    int x, y;
    FILE *f1, *f2;

    f1 = fopen("a.txt", "r");
    fscanf(f1,"%d %d", &x, &y);
    printf("%d %d", x, y); // check number

    f2 = fopen("b.txt", "w");
    fprintf(f2, "%d", x+y);

    fclose(f1);
    fclose(f2);
    return 0;
}