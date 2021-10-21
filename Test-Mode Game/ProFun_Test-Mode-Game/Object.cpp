#include "Object.h"
#include "main.h"
#include "Map.h"

void dropObject(Map* m, COORD pos) {
	int objRand = rand() % 5;
	_Object* obj = &m->Object[pos.Y][pos.X];
	unsigned int* sta = &m->State[pos.Y][pos.X];
	int* time = &m->Time[pos.Y][pos.X];
	switch (objRand) {
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
	COORD posOb = { posP->X + Len / 2, posP->Y };
	if (m->State[posOb.Y][posOb.X] == CAN_KEEP) {
		char Format = m->Object[posOb.Y][posOb.X].Format;

		if (Format == Life.Format) {
			//removeObject(m, posOb);
			p->Life++;
		}
		else if (Format == Potion.Format) {
			//removeObject(m, posOb);
			p->Bomb.PowerX++;
			p->Bomb.PowerY++;
		}
		else if (Format == newBomb.Format) {
			//removeObject(m, posOb);
			p->Bomb.Amount++;
		}
		removeObject(m, posOb);
	}
}

void removeObject(Map* m, COORD pos) {
	m->State[pos.Y][pos.X] = Space.NormalState;
	m->Object[pos.Y][pos.X] = { Space.Format, Space.Attribute };
}