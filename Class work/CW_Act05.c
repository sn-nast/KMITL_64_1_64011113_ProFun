// 64011113
// ProFun Activity 05 : Pointer
#include<stdio.h>
int main(){
    char str[100];
    char* ptr;
    ptr = str;
    printf("input   : ");
    scanf("%s", str);   // Array เป็น static pointer ไม่มี &
    
    printf("output  : ");
    while (*ptr != '\0'){
       if(*ptr != *(ptr + 1)){
           printf("%c", *ptr);
       }
       ptr++;
    }
    return 0;
}   