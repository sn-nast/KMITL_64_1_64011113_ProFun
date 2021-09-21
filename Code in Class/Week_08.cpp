// #include<stdio.h>
// int main()
// {
//     FILE* fp;
//     fp = fopen("mytestfile.txt", "w");
//     fprintf(fp, "%d %d %d\n", 100, 200, 500);
//     fclose(fp);
//     return 0;
// }

// #include<stdio.h>
// int main()
// {
//     FILE* fp;
//     int a, b, c, suma=0, sumb=0, sumc = 0;
//     fp = fopen("mytestfile.txt", "r");
//     while (!feof(fp)){
//     a = 0; b = 0; c = 0;
//     fscanf(fp, "%d %d %d", &a, &b, &c);
//     suma += a; sumb += b; sumc += c;
//     }
//     printf("%d %d %d\n", suma, sumb, sumc);
//     fclose(fp);
//     return 0;
// }



// #include<stdio.h>
// int main()
// {
// 	FILE *fptr;
// 	struct student {
// 		char name[20];
// 		char ID[9];
// 		int age;	
//         } s;
// 	fptr = fopen("StRecord.txt", "w");
// 	printf("Name : "); scanf("%s",s.name); 
// 	printf("ID : ");   scanf("%s",s.ID);   
// 	printf("Age : ");  scanf("%d",&s.age); 
// 	fwrite(&s, sizeof(struct student), 1, fptr);
// 	fclose(fptr);
// 	return 0;
// }

#include<string.h>
#include<stdio.h>
int main()  {
    struct player {
        char name[50];
        int level;
        int score;
    } x, y, z;
    strcpy(x.name,"Hello");
    player p;

    printf("Hello world");

}