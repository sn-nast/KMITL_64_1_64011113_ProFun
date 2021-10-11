#include "Map.h"
#include "main.h"
#include "Buffer.h"
#include "Object.h"

void setupMap(Map* m, int n_map) {
	for (short pY = 0; pY < MAP_HEIGHT; pY++) {
		for (short pX = 0; pX < MAP_WIDTH; pX++) {
			_Object* Ob = &m->Object[pY][pX];
			Ob->Format = planMap(n_map, { pX, pY });
			if (Ob->Format == Space.Format){
				Ob->Attribute = Space.Attribute;
				m->State[pY][pX] = Space.NormalState;
			}
			else if (Ob->Format == Wall_1.Format) {
				Ob->Attribute = Wall_1.Attribute;
				m->State[pY][pX] = Wall_1.NormalState;
			}
			else if (Ob->Format == Wall_2.Format) {
				Ob->Attribute = Wall_2.Attribute;
				m->State[pY][pX] = Wall_2.NormalState;
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
			{"|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"},
			{"||               #    #                                                            ||"},
			{"||               #####                                                             ||"},
			{"||               #####                                                             ||"},
			{"||               #   #                                                             ||"},
			{"||               # ###                                                             ||"},
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
			{"||                                                                                 ||"},
			{"||                                                                                 ||"},
			{"||                                                                                 ||"},
			{"||                                                                                 ||"},
			{"||                                                                                 ||"},
			{"||                                                                                 ||"},
			{"||                                                                                 ||"},
			{"||                                                                                 ||"},
			{"||                                                                                 ||"},
			{"||                                                                                 ||"},
			{"||                                                                                 ||"},
			{"||                                                                                 ||"},
			//{"||                                                             ##                  ||"},
			//{"||                                                               ##                ||"},
			{"|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"}

		};
		return map1[pos.Y][pos.X];
	}
	else if (n == 2) {
		;
	}
}

void changeStateMap(Map* m) {
	for (short pY = 0; pY < MAP_HEIGHT; pY++) {
		for (short pX = 0; pX < MAP_WIDTH; pX++) {
			if (m->State[pY][pX] == Bomb_burst.NormalState) {
				if (m->LastState[pY][pX] != Space.NormalState &&
					m->LastState[pY][pX] != Bomb_Nm.NormalState) { 
					dropObject(m, { pX, pY }); }
				else {
					m->State[pY][pX] = Space.NormalState;
					m->Object[pY][pX] = { Space.Format, Space.Attribute };
				}
			}
			_Object* Ob = &m->Object[pY][pX];
			putBuffer(pX, pY, Ob->Format, Ob->Attribute);
		}
	}
}

void Summary(Player* p, COORD pos) {
	setcolor(7, 1);
	gotoxy(pos.X, pos.Y + 1);
	printf_s("Player name\t: %s\n", p->Name);
	gotoxy(pos.X, pos.Y + 2);
	printf_s("Power in X\t: %d", p->Bomb.PowerX);
	gotoxy(pos.X, pos.Y + 3);
	printf_s("Power in Y\t: %d", p->Bomb.PowerY);
	gotoxy(pos.X, pos.Y + 4);
	printf_s("Life\t: %d", p->Life);
	gotoxy(pos.X, pos.Y + 5);
	printf_s("HAND\t: ");
}
