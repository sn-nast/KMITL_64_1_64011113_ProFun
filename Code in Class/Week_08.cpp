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

// #include<string.h>
// #include<stdio.h>
// int main()  {
//     struct player {
//         char name[50];
//         int level;
//         int score;
//     } x, y, z;
//     strcpy(x.name,"Hello");
//     player p;

//     printf("Hello world");

// }

#include<string.h>
#include<stdio.h>
int main()  {
    struct player {
        char name[50];
        int level;
        int score;
    } x, y, z;
    player p;
    FILE *f;
    f = fopen("Test.txt", "r");
    struct text
    {
        char i[100];
        int k;
    };
    text text1[5];
    int n = 0;
    while (!feof(f)){
        fscanf(f, "%d %s",&text1[n].k, &text1[n].i);
        printf("%d %s\n",text1[n].k, text1[n].i);
        n++;
    }
    fclose(f);

}
void readPoint() {
	FILE* f;
	fopen_s(&f,"HighScore_Player.txt", "r");
	int n = 0;
	int k;
	char t[100];
	while (!feof(f)) {
		//printf_s("n = %d\n", n);
		//fscanf_s(f, "%s %d", &PointHistory[n].Name, &PointHistory[n].Point);
		//printf_s("%s %d\n", PointHistory[n].Name, PointHistory[n].Point);
		fscanf_s(f, "%s %d", &k, &t);
		printf_s("%s %d\n", &k, &t);
		n++;
	}
	fclose(f);
}