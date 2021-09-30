// Level 3
// 64011113
/* 33.	 ให้นักศึกษารับข้อมูลเก็บใน array ขนาด 10 ช่องแล้วแสดงค่าตัวเลขต่างๆ ใน array 
และแสดงตัวเลขที่เลขข้างเคียงเป็นเลขคี่ ตัวอย่างการทำงานของโปรแกรม (แสดง Output หลังจากใส่ค่า Input) */
// Sol 2

#include<stdio.h> 
int checkMod(int x, int y){
    int mod_x, mod_y;
    mod_x = x - 2*(x/2);
    mod_y = y - 2*(y/2);
    if (mod_x == 1 && mod_y == 1){
        return 1;
    }
    return 0;
}

int main(){
    int n[10];
    printf("Data in Array : ");
    for(int i = 0; i <= 9 ; i++) {
        scanf("%d", &n[i]);
    }    
    printf("Result : ");
    for(int i = 0; i <= 8 ; i++) {
        if(checkMod(n[i - 1], n[i + 1]) == 1){
            printf("%d ", n[i]);
        }
    }  
    return 0;
}