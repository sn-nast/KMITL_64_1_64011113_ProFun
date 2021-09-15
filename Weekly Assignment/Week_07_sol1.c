// Level 3
// 64011113
/* 33.	 ให้นักศึกษารับข้อมูลเก็บใน array ขนาด 10 ช่องแล้วแสดงค่าตัวเลขต่างๆ ใน array 
และแสดงตัวเลขที่เลขข้างเคียงเป็นเลขคี่ ตัวอย่างการทำงานของโปรแกรม (แสดง Output หลังจากใส่ค่า Input) */
// Sol 1

#include<stdio.h> 
int main(){
    int n[10];
    printf("Data in Array : ");
    for(int i = 0; i <= 9 ; i++) {
        scanf("%d", &n[i]);
    }    
    printf("Result : ");
    for(int i = 0; i <= 8 ; i++) {
        if(n[i - 1] % 2 == 1 && n[i + 1] % 2 == 1){
            printf("%d ", n[i]);
        }
    }  
    return 0;
}