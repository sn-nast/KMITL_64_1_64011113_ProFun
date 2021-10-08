// Level 4
// 64011113
/* 63.	จงเขียนโปรแกรม Copy ไฟล์ข้อมูลโดยให้นักศึกษาป้อนข้อมูลของไฟล์ต้นทาง และข้อมูลไฟล์ปลายทาง */
// Sol 1

#include<stdio.h> 
#include<string.h>

int main(){
    struct _File {
        FILE *ptr;
        char path[BUFSIZ];
        int sum = 0;
    };
    _File inputFile[5], outputFile;

    // input file path
    strcpy(inputFile[0].path, "a.txt");
    strcpy(inputFile[1].path, "c.txt");

    // Add input file path
    // strcpy(inputFile[0].path, "....") ....

    // output file path
    strcpy(outputFile.path, "b.txt");

    int sumAll;
    for(int i = 0; i < sizeof(inputFile)/sizeof(_File); i++){
        if(strstr(inputFile[i].path, ".txt") == NULL) {break;} 

        inputFile[i].ptr = fopen(inputFile[i].path, "r");
        printf("File %s\n", inputFile[i].path );                // Check status
        printf("number\t: ", inputFile[i].path );               // Check status
        while(!feof(inputFile[i].ptr)){
            int num;
            fscanf(inputFile[i].ptr, "%d", &num);
            printf("%d ", num);                                 // Check status
            inputFile[i].sum += num;
        }
        // Sum of this file
        printf("\nsum\t: %d\n", inputFile[i].sum);              // Check status
        sumAll += inputFile[i].sum;

        printf("sumAll\t: %d\n\n", sumAll);                     // Check status
    }

    outputFile.ptr = fopen(outputFile.path, "w");
    fprintf(outputFile.ptr, "%d", sumAll);

    fclose(outputFile.ptr);

    for (int i = 0; i < sizeof(inputFile)/sizeof(_File); i++) { 
        fclose(inputFile[i].ptr);
    }
    return 0;
}