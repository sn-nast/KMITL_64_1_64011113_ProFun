#include "Map.h"
#include "main.h"
#include "Buffer.h"
void setupMap(int n) {
	;
}

void planMap1() {
	const int maxMapX = 96;
	const int maxMapY = 32;
	char map[maxMapY][maxMapX] = {
		{"||                                                                               ||"},
		{"||                                                                               ||"},
		{"||                                                                               ||"},
		{"||                                                                               ||"},
		{"||                                                                               ||"},
		{"||                                                                               ||"},
		{"||                                                                               ||"},
		{"||                                                                               ||"},
		{"||                                                                               ||"},
		{"||                                                                               ||"},
		{"||                                                                               ||"},
		{"||                                                                               ||"},
		{"||                                                                               ||"},
		{"||                                                                               ||"},
		{"||                                                                               ||"},
		{"||                                                                               ||"},
		{"||                                                                               ||"},
		{"||                                                                               ||"},
		{"||                                                                               ||"},
		{"||                                                                               ||"},
		{"||                                                                               ||"},
		{"||                                                                               ||"},
		{"||                                                                               ||"},
		{"||                                                                               ||"},
		{"||                                                                               ||"},
		{"||                                                                               ||"},
		{"||                                                                               ||"},
		{"||                                                                               ||"},
		{"||                                                                               ||"},
		{"||                                                                               ||"},
		{"||                                                                               ||"}
	};
	for (int iY = 0; iY < maxMapY; iY++) {
		for (int iX = 0; iX < maxMapX; iX++) {
			putBuffer(iX, iY, map[iY][iX], NORMAL_ATTIBUTE);
		}
	}
}