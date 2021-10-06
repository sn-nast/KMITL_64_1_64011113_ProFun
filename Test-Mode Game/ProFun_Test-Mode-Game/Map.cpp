#include "Map.h"
#include "main.h"
#include "Buffer.h"

void setupMap(_Map* m, int n_map) {
	char* Format;
	for (short pY = 0; pY < MAP_HEIGHT; pY++) {
		for (short pX = 0; pX < MAP_WIDTH; pX++) {
			*Format = m->Format[pY][pX];
			*Format = planMap(n_map, { pX, pY });
			unsigned int* State = &m->State[pY][pX];
			unsigned int* Attribute = &m->Attribute[pY][pX];
			if (*Format == ' ')				{ *State = 0; *Attribute = NORMAL_ATTIBUTE; }
			else if (*Format == SHARP_SYM)	{ *State = 1; *Attribute = NORMAL_ATTIBUTE; }
		}
	}
}

char planMap(int n, COORD pos) {
	char map[MAP_HEIGHT][MAP_WIDTH];
	char* p;
	if (n == 1) {
		char map1[MAP_HEIGHT][MAP_WIDTH] = {
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
			//{"||                                                                               ||"}
		};
		* p = map1[pos.Y][pos.X];
	}
	else if (n == 2) {
		;
	}
	//for (int iY = 0; iY < maxMapY; iY++) {
	//	for (int iX = 0; iX < maxMapX; iX++) {
	//		putBuffer(iX, iY, map[iY][iX], NORMAL_ATTIBUTE);
	//	}
	//}
	return* p;
}
