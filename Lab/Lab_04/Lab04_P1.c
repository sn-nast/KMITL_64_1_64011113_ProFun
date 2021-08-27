#include<stdio.h>
#include<string.h>
int main(){
    // รับข้อมูล
    char input[100]; 
    printf("input : ");
    scanf("%s", &input);
    int c = strlen(input);
    int Amount;
    // เช็คข้อมูล
    for(int n = 0; n < c; n++){
        int change = input[n];
        if (change >= '0' && change <= '9') {
                change -= '0';
                Amount = change;
        }
    // แสดงผล
        else if (change >= 'A' && change <= 'Z' && Amount >= 0) {
            for (int m = 1; m <= Amount; m++)  {printf("%c", input[n]);}
            Amount = 0;
        } 
        else {printf("%c", input[n]);}
    }
    return 0;
}