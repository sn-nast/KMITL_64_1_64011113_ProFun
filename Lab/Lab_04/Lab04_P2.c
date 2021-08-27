#include<stdio.h>
#include<string.h>
int main(){
    // รับข้อมูล
    char input[100]; 
    printf("input : ");
    scanf("%s", &input);
    int c = strlen(input);
    int Amount, noAmount = 1;
    // เช็คข้อมูล
    for(int n = 0; n < c; n++){
        int change = input[n];
        if (change >= '0' && change <= '9') {
            if(Amount > 0){
                change -= '0';
                Amount = Amount * 10 + change;        // แก้ไขจาก Test Script 6
            }
            else {Amount = change - '0';} 
            noAmount = 0;                             // แก้ไขจาก Test Script 7
        }
        else if (change >= 'A' && change <= 'z') {    // แก้ไขจาก Test Script 4
            if  (noAmount == 1)  {Amount = noAmount;} // แก้ไขจาก Test Script 7
    // แสดงผล
            for (int m = 1; m <= Amount; m++)  {printf("%c", input[n]);}
            Amount = 0;                             
            noAmount = 1;
        }
    }
    return 0;
}