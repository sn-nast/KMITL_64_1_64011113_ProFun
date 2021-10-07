#include "Map.h"
#include "main.h"
#include "Buffer.h"

void setupMap(Map* m, int n_map) {
	for (short pY = 0; pY < MAP_HEIGHT; pY++) {
		for (short pX = 0; pX < MAP_WIDTH; pX++) {
			_Object* Ob = &m->Object[pY][pX];
			Ob->Format = planMap(n_map, { pX, pY });
			if (Ob->Format == ' '){
				Ob->Attribute = Space.Attribute;
				m->State[pY][pX] = 0;
			}
			else if (Ob->Format == '#') {
				Ob->Attribute = Wall_1.Attribute;
				m->State[pY][pX] = 1;
			}
			else if (Ob->Format == '|') {
				Ob->Attribute = Wall_2.Attribute;
				m->State[pY][pX] = 2;
			}
			putBuffer(pX, pY, Ob->Format, Ob->Attribute);
		}
	}
}

char planMap(int n, COORD pos) {
	char p;
	char map[MAP_HEIGHT][MAP_WIDTH];
	if (n == 1) {
		char map1[MAP_HEIGHT][MAP_WIDTH] = {
			{"||\t\t\t               #   #                                                             ||"},
			{"||               #   #                                                             ||"},
			{"||               #   #                                                             ||"},
			{"||               #   #                                                             ||"},
			{"||               #   #                                                             ||"},
			{"||               #   #                                                             ||"},
			{"||               #   #                                                             ||"},
			{"||               #   #                                                             ||"},
			{"||               #   #                                                             ||"},
			{"||               #   #                                                             ||"},
			{"||               #   #                                                             ||"},
			{"||               #   #                                                             ||"},
			{"||               #   #                                                             ||"},
			{"||               #   #                                                             ||"},
			{"||               #   #                                                             ||"},
			{"||               #   #                                                             ||"},
			{"||               #   #                             ##                              ||"},
			{"||                                                 ##                              ||"},
			{"||                                                 ##                              ||"},
			{"||                                                 ##                              ||"},
			{"||                                                 ##                              ||"},
			{"||                                                 ##                              ||"},
			{"||                                                 ##                              ||"},
			{"||                                                 ##                              ||"},
			{"||                                                 ##                              ||"},
			{"||                                                 ##                              ||"},
			{"||                                                 ##                              ||"},
			{"||                                                 ##                              ||"},
			{"||                                                 ##                              ||"},
			{"||                                                             ##                  ||"},
			{"||                                                               ##                ||"}
		};
		return map1[pos.Y][pos.X];
	}
	else if (n == 2) {
		;
	}
}
