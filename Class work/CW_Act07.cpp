// 64011113
// ProFun Activity 07 : Text File / Binary File

#include<string.h>
#include<stdio.h>
int main() {
	int i, no_Player = 5;
	struct player {
		char name[50];
		int level;
		int score;
	} ;
	player p[10];
    player * ptr;
	for (i = 0; i < no_Player; i++) {
		strcpy(p[i].name, "Anonymous");
		p[i].level = i + 1 ;
		p[i].score = i * 100;
	}

	FILE *fptr = fopen("Player Data.txt", "w");
	fprintf(fptr, "Name\t\t");
	fprintf(fptr, "Level\t");
	fprintf(fptr, "Score\n");
	for (i = 0; i < no_Player; i++) {
		fprintf(fptr, "%s\t", p[i].name);
		fprintf(fptr, "%d\t", p[i].level);
		fprintf(fptr, "%d\n", p[i].score);
	}
	fclose(fptr);
	return 0;
}