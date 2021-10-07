// Level 4
// 64011113
/* 63.	จงเขียนโปรแกรม Copy ไฟล์ข้อมูลโดยให้นักศึกษาป้อนข้อมูลของไฟล์ต้นทาง และข้อมูลไฟล์ปลายทาง */
// Sol 2

#include<stdio.h> 

int main(){
    FILE *inputFile_ptr, *outputFile_ptr;
    char inputFile_path[100], outputFile_path[100];
    // input File path
    printf("input\t: ");
    scanf("%[^\n]%*c", inputFile_path);
    printf("output\t: ");
    scanf("%[^\n]%*c", outputFile_path);

    // copy file
    char ch;
    inputFile_ptr = fopen(inputFile_path, "r");
    outputFile_ptr = fopen(outputFile_path, "w"); 
    while((ch = fgetc(inputFile_ptr)) != EOF) {fputc(ch, outputFile_ptr);}
    fclose(inputFile_ptr);
    fclose(outputFile_ptr);
    return 0;
}