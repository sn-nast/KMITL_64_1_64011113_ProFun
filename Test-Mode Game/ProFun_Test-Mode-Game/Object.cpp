#include "Object.h"
#include "main.h"
#include "Map.h"

_Object
	Space = { ' ', NORMAL_ATTIBUTE, MAP_SPACE, NO_POINT},
	Wall[10] = {
		{ '#', 9,	CAN_DESTROYED,	WALL_POINT },
		{ '|', 10,	CANt_DESTROYED,	NO_POINT },
		{ '&', 11,	CANt_DESTROYED,	NO_POINT },
		{ '$', 10,	CANt_DESTROYED,	NO_POINT },
		{ '+', 11,	CANt_DESTROYED,	NO_POINT },
		{ '%', 6,	CAN_DESTROYED,	WALL_POINT },
		{ '=', 8,	CAN_DESTROYED,	WALL_POINT },
		{ 13, 12,	CANt_DESTROYED,	NO_POINT  },
		{ 'M', 12,  CAN_DESTROYED,  WALL_POINT}
	},
	Bomb_Nm		= {'@', 7,	BOMB_SHOW,	NO_POINT},
	Bomb_burst	= {'X', 4,	BOMB_BURST,	NO_POINT },
	Life		= { 3, 6,	CAN_KEEP,	ITEM_POINT },
	Potion		= { 'P', 100, CAN_KEEP,	ITEM_POINT},
	newBomb		= { 15, 12, CAN_KEEP,	ITEM_POINT }
;

int typeWall = sizeof(Wall) / sizeof(Wall[0]);

void dropObject(Map* m, COORD pos) {
	int* objRand = &m->ObjRand[pos.Y][pos.X];
	_Object* obj = &m->Object[pos.Y][pos.X];
	unsigned int* sta = &m->State[pos.Y][pos.X];
	int* time = &m->Time[pos.Y][pos.X];
	switch (*objRand % 5) {
		case 1: {
			*sta = Life.NormalState;
			*obj = { Life.Format, Life.Attribute, Life.NormalState };
			*time = 1000;
			break; 
		}
		case 2: {
			*sta = Potion.NormalState;
			*obj = { Potion.Format, Potion.Attribute, Potion.NormalState }; 
			*time = 1000;
			break; 
		}
		case 3: {
			*sta = newBomb.NormalState;
			*obj = { newBomb.Format, newBomb.Attribute, newBomb.NormalState };
			*time = 1000;
			break; }
		//case 4: {
		//	*sta = Life.NormalState;
		//	*obj = { Life.Format, Life.Attribute, Life.NormalState };
		//	break; }
		default: {
				*sta = Space.NormalState;
				*obj = { Space.Format, Space.Attribute, Space.NormalState };
			break;
		}
	}
}

void keepObject(Player* p, Map* m) {
	unsigned int Len = p->Lenght;
	COORD* posP = &p->Position;
	COORD posOb = *posP;
	if (m->State[posOb.Y][posOb.X] == CAN_KEEP) {
		char Format = m->Object[posOb.Y][posOb.X].Format;
		if (Format == Life.Format) {
			p->Point += Life.Point;
			p->Life++;
		}
		else if (Format == Potion.Format) {
			p->Point += Potion.Point;
			p->Bomb.PowerX++;
			p->Bomb.PowerY++;
		}
		else if (Format == newBomb.Format) {
			p->Point += newBomb.Point;
			p->Bomb.Amount++;
		}
		int Len = p->Lenght;
		int Hei = p->Height;
		for (int H = 0; H < Hei; H++) {
			for (int L = 0; L < Len; L++) {
				removeObject(m, { (SHORT)(posOb.X + L), (SHORT)(posOb.Y + H)});
			}
		}
	}
}


void removeObject(Map* m, COORD pos) {
	m->State[pos.Y][pos.X] = Space.NormalState;
	m->Object[pos.Y][pos.X] = { Space.Format, Space.Attribute };
}