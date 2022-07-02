#include "Point.h"
#include "main.h"
#include "Buffer.h"
_PointHistory PointHistory[5];
FILE* f;
int size = sizeof(PointHistory) / sizeof(PointHistory[0]);

void readPoint() {
	int CountPlay = 0;
	f = fopen("00 HighestPoint.txt", "r");
	while (!feof(f)) {
		fscanf(f, "%s\t\t%d", &PointHistory[CountPlay].Name, &PointHistory[CountPlay].Point);
		CountPlay++;
	}
	fclose(f);
	for (int n = 0; n < size; n++) {
		if (PointHistory[n].Point == 0) {
			strcpy(PointHistory[n].Name, "------");
		}
	}
}

void arrangePoint() {
	for (int i = 0; i < size; i++) {
		for (int j = i + 1; j < size; j++) {
			if (PointHistory[i].Point < PointHistory[j].Point) {
				int tempPoint = PointHistory[i].Point;
				char tempName[50];
				strcpy(tempName, PointHistory[i].Name);
				PointHistory[i].Point = PointHistory[j].Point;
				strcpy(PointHistory[i].Name, PointHistory[j].Name);
				PointHistory[j].Point = tempPoint;
				strcpy(PointHistory[j].Name, tempName);
			}
		}
	}
	f = fopen("00 HighestPoint.txt", "w");
	for (int n = 0; n < size; n++) {
		fprintf(f, "%s\t\t%d\n", PointHistory[n].Name, PointHistory[n].Point);
	}
	fclose(f);
	readPoint();
}

void recordPoint(Player* p) {
	Map* m = &playMap[mapSelected];

	f = fopen("00 PlayHistory.txt", "a");
	fprintf(f, "%s\t\t%d\n", p->Name, p->Point);
	fclose(f);
	if (p->Point > PointHistory[size - 1].Point) {
		PointHistory[size - 1].Point = p->Point;
		strcpy(PointHistory[size - 1].Name, p->Name);
		arrangePoint();
	}
	readPoint();
}

void showHighestPoint(COORD start) {
	gotoxy(start.X, start.Y++);
	printf("%*s%*s", 20 + (strlen("Highest Points") / 2), "Highest Points" , 20 - (strlen("Highest Points") / 2), "");
	gotoxy(start.X, start.Y++);
	printf("---------------------------------------");
	gotoxy(start.X, start.Y++);
	printf("|%4s%-1s| %13s%-3s | %8s%-2s |", "No.", "", "Player Name", "", "Points", "");
	gotoxy(start.X, start.Y++);
	printf("|%4s%-1s| %15s%-1s | %10s%0s |", "---", "", "---------------", "", "---------", "");
	for (int n = 0; n < size; n++) {
		gotoxy(start.X, start.Y++);
		if (n == 0) { setcolor(15, 4); }
		else if (n == 1) { setcolor(0, 14); }
		else if (n == 2) { setcolor(15, 1); }
		else { setcolor(15, 0); }
		printf("|  %d  | %-16s | %10d |" ,n + 1, PointHistory[n].Name, PointHistory[n].Point);
	}
	gotoxy(start.X, start.Y++);
	printf("---------------------------------------");
	gotoxy(start.X, start.Y++);
	printf("| %*s%*s | %10d |", 11 + (strlen(playerMe.Name)/2), playerMe.Name, 11 - (strlen(playerMe.Name)/2), "", playerMe.Point);
	gotoxy(start.X, start.Y++);
	printf("---------------------------------------");
}