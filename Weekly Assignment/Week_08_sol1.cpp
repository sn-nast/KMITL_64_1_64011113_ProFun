// Level 4
// 64011113
/* 63.	จงเขียนโปรแกรม Copy ไฟล์ข้อมูลโดยให้นักศึกษาป้อนข้อมูลของไฟล์ต้นทาง และข้อมูลไฟล์ปลายทาง */
// Sol 1

#include<stdio.h> 

int main(){
    struct copyFile {
        FILE *ptr;
        char path[BUFSIZ];
    };
    copyFile inputFile, outputFile;

    // input File path
    printf("input\t: ");
    scanf("%[^\n]%*c", inputFile.path);
    printf("output\t: ");
    scanf("%[^\n]%*c", outputFile.path);

    // copy file
    inputFile.ptr = fopen(inputFile.path, "r");
    outputFile.ptr = fopen(outputFile.path, "w"); 
    while(!feof(inputFile.ptr)){
        char ch;
        fscanf(inputFile.ptr, "%c", &ch);
        fprintf(outputFile.ptr,"%c", ch);
    }
    fclose(inputFile.ptr);
    fclose(outputFile.ptr);
    return 0;
}